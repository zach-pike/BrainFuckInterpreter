, get user input

> next tape spot
set to 48 
++++++++++++++++++++++++++++++++++++++++++++++++

subtract ascii value minus 48 to get raw int
[<->-]<
>
, get user input

> next tape spot
set to 48 
++++++++++++++++++++++++++++++++++++++++++++++++

subtract ascii value minus 48 to get raw int
[<->-]<<

[ outer adder loop
  > copy second looping number
  [
    >+ real copy
    >+ backup to copy to original
    <<- decrement
  ]
  >> restore second loop after copy
  [
    <<+
    >>-
  ]
  < set pointer to helper secondary loop num
  [ do the incrementation (multiply)
    >>+
    <<-
  ]
  <<-
]
>>>>
!

[-]++++++++++.