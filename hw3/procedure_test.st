{%
 % Example with Functions
 %}

% global variables
const a: int := 5
var c: int

% function declaration
procedure add (a: int, b: int)
  put a+b
end add

% main block
add(a, 10)
if (c > 10) then
  put -c
else 
  put c
end if
put "Hello World\n"
