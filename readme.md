# My brainfuck interpreter
This is a suped up brainfuck interpreter I made in school. It contains a few extra features some people may find useful

# Use
First make a `dist` folder

Run `./build.sh` to build the program

Then the CLI follows as so
```
./bf [--minify -in <filepath> -out <outfile>] [--unfuck] <path/to/file/to/run>
```

`--unfuck`: Tell the interpreter to use my extra helper commands


`--minify`: takes a input file with `-in` and removes all comments from it and writes it to `-out`

## Using `--unfuck`
The `--unfuck` flag tells the interpreter to parse my special commands i added for help with BrainFuck

### The commands
`!`: Prints the interger value at the memory pointer

`#`: Read a interger from `stdin` ans store it at the memory pointer

`?`: Debugging, prints out info about the mempry pointer address and the interger value stored there