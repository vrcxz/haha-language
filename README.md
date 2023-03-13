## Haha Language
This is my take on making my own basic esoteric interpreted shell programming language, named `Haha` for fun. This is just a very basic interpreter, coded only in a few days (with a lot of other days looking at tutorials and designing prototypes) as a beginner in C++, so it goes without saying: use it on your own risk. <sub>It might even explode.</sub>

---

### Contents
- [Printing "Hello World!"](#pri)
- [Variables]()
- [Increment and Decrement]()
- [Newlines]()
- [System Commands]()
- [Conditions]()
- [Control Flow]()
- [Simple Game]()


---

### <a id="pri">Printing "Hello World!"</a>
What's an introduction to a programming language without starting at the famous `Hello World!`? To print a `Hello World!` program, make a new file named `helloworld.haha`, and use the `haha` keyword to print text to the console:

```
haha Hello World!
```
Output: `Hello World!`

We don't use double quotes because `haha` always expect string literals as its subsequent argument. In order to print variables, we use `hahaha`.

```
hahaha x
```
This prints a variable named `x`.

`Note: Keywords MUST always be placed at the start of a line. Otherwise, it will be considered a comment.`

```
This is a comment!
  haha This also now a comment!
```

---

### Variables
`Haha` has only two data types: a signed integer (`ha`) and a string (`ah`).

Here's an example of a variable declaration:
```
ha x 10
ah text What da dog doin
```

To take an input and store it to a variable, you can use `hhaa`.

```
ha x 0
hhaa x
hahaha x
```

This declares a signed integer variable `x` initialized as 0 at its definition. It then proceeds to request an input from the user to store in the `x` variable— then prints it out to the console.

---

### Increment and Decrement
To increment/decrement an `ha` variable, you can use `a` (named after my silent scream after finding out my incapability to add arithmetic operations/lisp in this language).

```
a ++ x
a -- x
```

---

### Newlines

`Haha` doesn't read a newline symbol (`\n`). So in order to create one, you use `h`. It takes an integer as its subsequent argument to print how many newlines you want.

This prints out 1 newline:
```
h 1
```

This prints out 1000 newline (yeh):
```
h 1000
```
---

### System commands
To execute commands on the system console, you can use `aah`.


For clearing the screen.
```
aah clear
```

For viewing the current date.
```
aah date
aah time
```

---

### Conditions
To start a condition, you can use the `haa` keyword, ending with `he` to break the condition.

```
ha x 10
ha y 5
haa x < y
haha x
he
```
Nothing will be printed to the console with this program (because 10 isn't greater than 5).

`haa` only takes an integer variable as its argument.

`Note: Nested haa is not supported. Trying to nest haa statements will result in unexpected things occurring. I warned you.`

---

### Control Flow
In order to iterate through a series of keywords, you can use `haahaa`, followed by an `ah` variable argument, and ending with `hehe` to break the iteration.

```
ha x 5
haahaa x
hahaha x
a ++ x
hehe
```
Output: `56789`

`Note: If you didn't add an argument to haahaa, it will automatically evaluate to 1. Nested iterations here are also a no-no.`



---

### Warning
This is my very first time creating my own programming language, so expect that there would be a LOT of edge cases (also zero error handling).  I'm simply relatively inexperienced in the end, so constructive criticisms are always welcomed!

#### License
MIT
