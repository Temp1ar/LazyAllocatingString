#include <iostream>
#include <string>

class String 
{
public:
	String() 
	{
	}

	String(const std::string& content) 
	{
		content_ = content;
	}

	operator std::string() 
	{
		return content_;
	}

	const String& operator=(const String& temp) 
	{
		content_ = temp.content_;
		return *this;
	}

	template<class Type>
	const String& operator=(Type temp) 
	{
		size_t newSize = temp.size();
		content_.reserve(newSize);
		temp.build(content_);
		return *this;
	}

	size_t size() const 
	{
		return content_.size();
	}

	void build(std::string& s) const 
	{
		s.insert(s.end(), content_.begin(), content_.end());
	}

private:
	std::string content_;
};

template<class Ref1, class Ref2>
class InternalString 
{
	const Ref1& ref1_;
	const Ref2& ref2_;
public:
	InternalString(const Ref1& ref1, const Ref2& ref2) 
		: ref1_(ref1)
		, ref2_(ref2)
	{}

	size_t size() const 
	{
		return ref1_.size() + ref2_.size();
	}


	void build(std::string& s) const 
	{
		ref1_.build(s);
		ref2_.build(s);
	}
};

template <class Ref1, class Ref2>
InternalString<Ref1, Ref2> 
	operator+(const Ref1& str1, const Ref2& str2) 
{
	return InternalString<Ref1, Ref2>(str1, str2);
}

int main() 
{
	String s, a("abcshadjkasdkjas"), b("bcdasdhjkasdhkas"), c("cdeskdhjoqihfrq");
	s = a + b + c;
}