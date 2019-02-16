# KURUKSHETRA

###Usage of Collider Class

Inside `Player` and `Platform` classes, a member function `GetCollider()` is defined, which calls `Collider()` constructor.
 
 To check for collision of players 
or player and platforms use the `GetCollider()` member function with `CheckCollision()` member function of the `Collider` class.

example:

`player1.GetCollider().CheckCollision(platform1.GetCollider())`


This return a `true` if `player1` and `platform1` collide and returns `false` if not.  