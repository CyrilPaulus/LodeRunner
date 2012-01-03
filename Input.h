/* 
 * File:   Input.h
 * Author: cyril
 *
 * Created on January 3, 2012, 12:06 PM
 */

#ifndef INPUT_H
#define	INPUT_H


struct Input {
  bool Left;
  bool Right;
  bool Up;
  bool Down;

  Input() {
    Up = Down = Left = Right = false;
  }

  bool operator==(const Input& in) {
    return (Up == in.Up && Down == in.Down && Right == in.Right && Left == in.Left);
  }

  Input& operator=(const Input& rhs) {
    Up = rhs.Up;
    Down = rhs.Down;
    Left = rhs.Left;
    Right = rhs.Right;
    return *this;
  }
};

#endif	/* INPUT_H */

