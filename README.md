# ncurses Background and "Hello World!"

(This is a complete script of the video for reference)

Hey guys, and welcome to my tutorial series on NCURSES. I intend this series to be a reboot of a series that I previously did. This time I will be going more in-depth about the NCURSES library while still keeping it easy to understand. If you are unfamiliar with what NCURSES is, these two websites here do a really good job of explaining it, and I will be loosely basing my tutorials off of information from both of these sources.

NCURSES (or CURSES) is a library of routines that makes it easy to display characters on a variety of different terminals. Because certain terminals support some features while others don't, and because certain terminals implement the same features differently, the programmer must somehow handle these differences. Instead of having to learn how each terminal displays characters or colors, the programmer can just tell NCURSES to do something and it will figure out how to do that for the specific terminal it is run on.

I will be using the C version of the NCURSES library, which is one of the most well-known versions. However, there are other languages which also support NCURSES. Off the top of my head I know that Python has a version as well. A lot of the information you learn here will extend to that and other versions, because the underlying library remains the same, with only minor differences in syntax because of the language surrounding the NCURSES routines.

This will by no means be a C tutorial. I will do my best to explain any code that I write but I recommend a background in either C or C++ before watching this tutorial.

I will provide links below to sources which explain how to install NCURSES on a variety of systems, though it may already be installed on your system. I will not be showing how to install and use PDCurses on Windows as I have never had a lot of luck getting that to run properly or reliably, so I apologize to anyone running on windows. You'll notice that I am working in a windows environment, but I am actually ssh-ing into a remote linux machine and running ncurses from there.

As a quick note, I will often use the general word "routine" instead of "function" or "macro" because the NCURSES library contains a mixture of the two kinds of sequences of commands. I will try to make sure to indicate when a routine is a macro and not a function, particularly if it is important to that routines implementation or understanding how it works.

So let's get started. The first thing to do is to make a new C file that we can import NCURSES into. Lets call this file `hello.c`, the astute in the audience may see where this is going. 

I'll be using the vim editor for these tutorials, but any plain text editor will do. The first order of business is to include the ncurses library:

```c
#include <curses.h>
```

You may notice that instead of `ncurses.h` the include is for `curses.h`. I won't go too much into detail, but essentially NCURSES is an open source clone of the original CURSES library. Nowadays, the two are almost interchangeable and you'll hear me refer to both. Essentially though, either include will work. I have gotten in the habit of using `curses.h` and the tutorials I referenced earlier also use `curses.h`.

Now NCURSES is really nice and gives you a couple includes for free: `stdio.h` is included for all systems, and either `termios.h`, `termio.h`, or `sgtty.h` depending on the system you are running on. This doesn't prevent you from including them yourself, but it's a nice convenience.

Next, just like all C programs, we need a main function to actually run our program:

```c
int main(int argc, char **argv) {

  return 0;
}
```

Now that we have the foundation, we can begin using NCURSES. NCURSES has what I like to call "routine wrappers", which are essentially two function calls which your NCURSES code must be placed between in order to work properly. These two functions are `initscr()` and `endwin()`.

```c
int main(int argc, char **argv) {
  initscr();

  endwin();

  return 0;
}
```

The routine `initscr()` performs two necessary functions, and must be called before performing any screen routines. It collects information about the terminal characteristics so it can accurately display colors, characters, etc, and it also allocates space for two special variables called `curscr` and `stdscr`. These variables are of type WINDOW, which is an NCURSES data type or structure which is used to describe the state of the terminal screen. It stores the starting position of the screen and its size. A window is like an internal representation of the screen that only the computer understands however, and making changes to a window does not immediately make changes to the terminal screen.

`curscr` represents what the current screen looks like and should not be changed, whereas `stdscr` is what the screen should look like next and is the default window to write and make changes to.

`endwin()` is like the NCURSES cleanup routine. It restores tty modes to what they were when `initscr()` was first called, and moves the cursor down to the lower-left corner. This routine should be called before exiting the program to avoid strange side effects.

Between these two functions, we can perform NCURSES routines. Lets run what we have now and see what happens.

In order to compile a C file which includes curses, we need to link the ncurses library with the flag `-lncurses`. For the program I have created, I will write `gcc -lncurses hello.c -o hello` to create a program called `hello` from our `hello.c` file. For this tutorial I will just compile from the command line, but in future tutorials I will be using a makefile to compile.

```sh
gcc -lncurses hello.c -o hello
```

And now if we run that program...

```sh
./hello
```

You'll notice that nothing actually happens. And this actually makes sense, because essentially what we have done here is tell ncurses to start, and then immediately stop and then the program exits. In order to actually get something to display, and for long enough that a human can actually see it, we will need two additional routines.

The first routine, `getch()`, reads a single character from the `stdscr`. The official specification says that `getch()` may be implemented as a macro. This routine's behavior can be configured through other routine's, but for the scope of this tutorial we will just use the default configuration which waits until the user presses a key, and then returns the integer value of the character which was pressed. This function blocks the program from executing which gives us as humans time to read what is displayed.

The second routine, `refresh()`, updates the visible window to match the contents of `stdscr`. As we gradually make changes to the `stdscr`, they are not updated and displayed. Only when `refresh()` is called do changes become visible. The official spec also notes that `refresh()` may be implemented as a macro.

Now if we combine these two routines, we can refresh the screen to show changes, and then we can call `getch()` in order to stop execution until we want to continue.

```c
initscr();

refresh();
// Doesn't capture key input because we don't need it yet...
getch();

endwin();
```

Now if we run this... we should she a blank screen. Essentially, `initscr()` created `stdscr` as an empty window, so when we refresh the screen to match `stdscr` it fills the terminal with empty cells as nothing has been added to it yet. As soon as we press a character, the program will exit back to the command line.

Now that we can pause the program and see our changes, lets actually output something to the screen! To do this, we are going to use a routine called `printw()` which takes a formatted string as its first argument.

```c
initscr();

printw("Hello World!");

refresh();
// Doesn't capture key input because we don't need it yet...
getch();

endwin();
```

And at last we are finally getting somewhere! For the sake of completeness, I should mention that `printw()` is essentially just NCURSES version of `printf()` and can be supplied with the same types of formatted strings, and fed a series of optional arguments afterwards to be inserted into the string. For instance:

```c
printw("Hello, %s!", "Bob");
```
