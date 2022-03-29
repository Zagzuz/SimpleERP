#ifndef STATEFUL_H
#define STATEFUL_H

#include <string>
#include <deque>


namespace SERP
{
	class Stateful
	{
	public:
		Stateful(std::size_t state_capacity);
		virtual void save_state() = 0;
		bool undo(std::size_t steps = 1);
		bool redo(std::size_t steps = 1);
		void clear_history();
		void set_state_capacity(std::size_t new_capacity);
		std::size_t get_state_capacity() const;
	protected:
		virtual void load_state(std::size_t index) = 0;
		std::size_t cur_state_;
		std::deque<std::string> states_;
	private:
		std::size_t state_cap_;
	};
} // namespace SERP

#endif // STATEFUL_H