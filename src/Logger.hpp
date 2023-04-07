
namespace Logger {

	enum TraceLevels {
		Trace,
		Debug,
		Info,
		Warning,
		Error,
		Fatal
	};

	class TraceMessage {
	public:
	private:
		const char* message;
		const TraceLevels level;
	};

	inline void log();
}