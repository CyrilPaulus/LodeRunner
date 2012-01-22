/* 
 * File:   Singleton.h
 * Author: cyril
 *
 * Created on January 20, 2012, 6:04 PM
 */

#ifndef SINGLETON_H
#define	SINGLETON_H

template <typename T> 
class Singleton {
    
public:
    static T *getInstance(void) {
        if(instance == 0)
            instance = new T;
        return instance;
    }
    
    static void release(void) {
        if(instance != 0) {
            delete instance;
            instance = 0;
        }
    }
    
protected:
    Singleton(void) {}
    ~Singleton(void) {}
    
private:
   Singleton(Singleton const&);
   Singleton& operator=(Singleton const&);
    static T *instance;
};

template <class T> T* Singleton<T>::instance=NULL;


#endif	/* SINGLETON_H */

