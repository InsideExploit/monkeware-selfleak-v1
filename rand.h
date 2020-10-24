#pragma once

std::string random_string(int len)
{
	static const std::string allowed_chars{ "AKNCNPLAXøŞÂ3šÆxIòªm'+ÿÍã315-+=][" };
	static thread_local std::default_random_engine randomEngine(std::random_device{}());
	static thread_local std::uniform_int_distribution<int> randomDistribution(0, allowed_chars.size() - 1);
	std::string id(len ? len : 32, '\0');
	for (std::string::value_type& c : id) {
		c = allowed_chars[randomDistribution(randomEngine)];
	}
	return id;
}