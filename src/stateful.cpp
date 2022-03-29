#include "stateful.h"


namespace SERP
{
	Stateful::Stateful(std::size_t state_capacity) : state_cap_(state_capacity)
	{
		cur_state_ = 0;
	}

	bool Stateful::undo(std::size_t steps)
	{
		if (cur_state_ < steps) return false;
		if (steps) load_state(cur_state_ -= steps);
		return true;
	}

	bool Stateful::redo(std::size_t steps)
	{
		if (states_.size() - cur_state_ < steps + 1) return false;
		if (steps) load_state(cur_state_ += steps);
		return true;
	}

	void Stateful::clear_history()
	{
		cur_state_ = 0;
		state_cap_ = 0;
		states_.clear();
	}

	void Stateful::set_state_capacity(std::size_t new_capacity)
	{
		if (!new_capacity)
		{
			clear_history();
			return;
		}
		if (state_cap_ > new_capacity)
		{
			std::size_t difference = state_cap_ - new_capacity;
			std::size_t space_left = state_cap_ - cur_state_ + 1;
			std::size_t i, j;
			if (difference > space_left)
			{
				i = difference;
				j = state_cap_;
				cur_state_ -= i;
			}
			else
			{
				i = cur_state_;
				j = cur_state_ + difference;
				cur_state_ = 0;
			}
			states_.erase(states_.begin(), std::next(states_.begin(), i));
			states_.erase(std::next(states_.begin(), j), states_.end());
		}
		state_cap_ = new_capacity;
	}

	std::size_t Stateful::get_state_capacity() const
	{
		return state_cap_;
	}

} // namespace SERP