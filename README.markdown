
This library is intended to be a useful set of extensions to the WPI-provided
library, providing reliable concurrency and diagnostics. However, parts of it
have to be explained. The socket library is pretty simple; it's basically an
abstraction over berkeley sockets. However, the concurrency and sockets code
needs some explanation.

Concurrency
===========

Most of the concurrency code is an abstraction over pthreads, which in this case
is also an abstraction over the vxworks threads. We may or may not change this
to vxworks threads (notable advantages of this are threads showing up as named
in the diagnostics section of wind river). The main advantage we have over just
starting pthreads is that if an object inherits from thread::start, similar to
the 'Runnable' interface in java, the entry point of the thread will call the
member function 'run(void*)' of that object, allowing the use of member
variables and methods.

Diagnostics
===========

Diagnostics were tricky; we aimed to have a simple interface that allows you to
register an input or an output and have it show up on a web interface. To do
this, we implemented an interface (pure virtual class), which we then created
(or will create, at the time of writing) concrete subclasses for each of the
sensors/effectors in wpilib. We had to do this since none of the sensors really
shared a useful interface to get or set them. However, it does mean that you
can call diagnostics_center#register_device() with any wpilib sensor, without
the need to wrap it in an intermediary (or rather, it gets wrapped in an
intermediary implicitly). Since this can be fairly confusing, an example
follows:

<script src="http://gist.github.com/608688.js"> </script>

Build Environment
=================

[cb8a82](https://github.com/Nashoba-Robotics/Nashoba-Robotics/commit/cb8a82474e66d344a5c97276629c887c07193a06) in the closed loop branch enables the following macros:
NR_CLOSED_LOOP_CONTROL - Switches drive code to closed loop control when set.
