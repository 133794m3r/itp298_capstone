/*
* ITP-298 Capstone Project
* Group: Dangling Pointers
* Macarthur Inbody && Nathaniel Mullins
*/
//This file will contain all of the vector related templates we need.
#ifndef ITP298_CAPSTONE_VECTORS_HXX
#define ITP298_CAPSTONE_VECTORS_HXX

template <class T,class Allocator> std::ostream& operator<<(std::ostream& os, const std::vector<T,Allocator> &m){
	size_t m_size=m.size();
	os << "[";
	for(size_t i=0; i < m.size(); i++) {
		os << m[i]  <<(i == m_size - 1 ? "" : ",");
	}
	os << "]" << std::endl;
	return os;
}
template <class T,class Allocator> std::istream& operator>>(std::istream& is, std::vector<T,Allocator> &m){
	size_t n=m.size();
	for(size_t i=0;i<n;i++){
		is >> m[i];
	}
	return is;
}

#endif //ITP298_CAPSTONE_VECTORS_HXX
