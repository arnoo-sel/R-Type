#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template<typename T> class Singleton
 {
   public:
	 static T& instance()
	 {
		 static T _instance;
		 return _instance;
	 }
 };

#endif // SINGLETON_HPP
