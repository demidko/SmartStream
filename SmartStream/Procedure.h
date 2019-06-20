#include "SmartStream.h"

struct Procedure
{
    Procedure(const std::string_view &s)
	{
        SmartStream::io << "Процедура " << s << " начата: "<< SmartStream::tab;
	}
	
	~Procedure()
	{
	    SmartStream::io<<SmartStream::untab << "Процедура " << s << " завершена.";
	}
}