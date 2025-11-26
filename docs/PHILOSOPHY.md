# the philosophy and why ezcli just "clicks" for me

i always go through this with my own projects, or also when i see neatly done
ones. but the concept of taking structurally sound and logical building blocks
that are also not too big to swallow just makes some very satisfying buttons
click in my head.

these building blocks should also be necessary or way too useful to not be
included.

## there is SUCH a thing as too much abstraction

personally, i hate libraries with so much abstractions it feels like you're
writing python. the programmer doesn't need that much handholding. i mean
sure, i am stupid, but somebody accepting that annoys me to my core.

## ezcli is the tool, not the ultimate way

this misunderstanding between a goal and the means to getting to that goal
is why we started seeing terms like "experienced react developer". like,
do you help maintain react, if no, then hell nah.

too much opinions bundled in something that many people use isn't always nice.
i could have also added interactivity, input type enforcement, some structs to
use for contexts, and all other bundled shit that comes with some libraries.

and sure, maybe that would save you some time, but how much code should a person
write for you before they program your whole application? you might not like
all of my methods to approach things, something you want to change in ezcli
might just be too internal to change, or here comes the worst part: you could use
some of that code without even understanding it (THAT my friend, is the root of
most bugs).

## there is a philosophy to c many people forget

i recently saw a library that used macros to let someone create artificial
function definitions, and nest them in order too (cli>arg>usage),
and names, the usages, the descriptions were all taken inside a single string
as an argument to some of those "functions".

i'm not kidding you, dennis ritchie would stab you with a fork if he was alive
to see your implementations.

stop creating your own languages with macros, stop making everything so easy
its not descriptive anymore. storing information in strings is done with yml,
csv, and json files. not c. also, use python if you want nested functions. also,
that implementation requires at least 4-5 levels of indentation or hundreds of
modules to be created that also require hundreds of header files.
