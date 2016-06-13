#include <exception>
#include <string>

namespace GF {
	namespace Core {
		class Exception :public std::exception {
		public:
			Exception(std::string message = "", int code = 0);
			~Exception();
			std::string getMessage();
			int getCode();

		private:
			int code_;
			std::string message_;
		};
	}
}