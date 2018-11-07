#include "network.h"
#include "random.h"
#include <iostream>

size_t Network::size() const
{
	return values.size();
}

size_t Network::degree(const size_t &_n) const
{
	return links.count(_n);
}

 void Network::resize(const size_t& n)
 {
	 if (n>0) {
		 values.clear();
		 values.resize(n);
		 RNG.normal(values,0, 1);
 }
}
 bool Network::add_link(const size_t& a, const size_t& b)
 {
	 if(a==b or a>=values.size() or b>=values.size()) return false;
	 for(auto link:links)
	 {
		 if((link.first==a and link.second==b)and(link.first==b and link.second==a)) return false;
	 }
	 links.insert({a,b});
	 links.insert({b,a});
	 return true;
 }
 
 size_t Network:: set_values(const std::vector<double>& v)
 {
	 if(v.size()<=values.size()) {
		 for(size_t i=0; i<=v.size();++i) {
			 values[i]=v[i];
			}
		 return v.size();
	 }
	 if(v.size()>values.size())
	 {
		 for(size_t i=0; i<=values.size();++i)
		 {
			 values[i]=v[i];
		 }
		 return values.size();
	 }
 }

double Network::value(const size_t &n) const
{
	if(values.size()>n){
	return values[n];}
	return 0;
}

std::vector<double> Network ::sorted_values() const
{
	std::vector<double>sorted(values);
	std::sort (std::begin(sorted), std::end(sorted));
	std::reverse (std::begin(sorted), std::end(sorted));
	return sorted;
}

std::vector<size_t> Network::neighbors(const size_t& a) const
{
	std::vector<size_t> neighbors;
	neighbors.clear();
	for(auto valeur: links){
		if(valeur.first == a){
		neighbors.push_back(valeur.second);
		}
	}
	return neighbors;
}

size_t Network::random_connect(const double& mean)
{
	links.clear();
	size_t nbLiens(0);
	std::vector<int> connectednodes(1);
	for(size_t i=0; i<values.size()-1; ++i){
		int degree=RNG.poisson(mean);
		if (degree> values.size()-1)
		{degree=values.size()-1;}
		
		for(int j=0; j<degree; ++j){
			do {
				RNG.uniform_int(connectednodes,0,values.size()-1);
				}
				while (not(add_link(i,connectednodes[0])));
				++nbLiens;
			}
		}
		return nbLiens;
}
