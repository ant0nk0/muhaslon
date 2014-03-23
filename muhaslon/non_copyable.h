#pragma once

class NonCopyable
{
public:
	NonCopyable() {}

private:
	NonCopyable(const NonCopyable&);
	void operator=(const NonCopyable&);
};