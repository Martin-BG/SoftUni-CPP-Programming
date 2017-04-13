#pragma once

#include<vector>

class Utils
{
public:
	template <typename T>
	static std::vector<T>& insert(std::vector<T>& target, const std::vector<T>& source) 
	{
		target.insert(target.end(), source.begin(), source.end());
		return target;
	}

	template <typename T>
	static std::vector<const T*> toConst(const std::vector<T*> v)
	{
		std::vector<const T*> vConst;

		for (T* item : v)
		{
			vConst.push_back(item);
		}

		return vConst;
	}
};

