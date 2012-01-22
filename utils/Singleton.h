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
    static T *getInstance() {
        if(instance == 0)
            instance = new T;
        return instance;
    }
    
    static void release() {
        if(instance != 0) {
            delete instance;
            instance = 0;
        }
    }
    
protected:
    Singleton() {}
    ~Singleton() {}
    
private:   
    static T *instance;
};

template <class T> T* Singleton<T>::instance=NULL;


#endif	/* SINGLETON_H */

