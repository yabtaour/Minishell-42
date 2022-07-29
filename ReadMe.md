<!-- remark -->
<!-- del those functions -->
<!-- strlen -->
<!---strcpy--->
<!-- strcmp -->
<!-- calloc -->
<!-- strncmp -->

maybe free in strjoin

1 => alpha / number 
2 => pipe 
4 => space 
5 => " 
6 => ' 
7 => +/* 
8 = {} 
9 = () 
10 = <> 
11 => $ 
12 => &  
13 => - 
14 => = 
15 => . 


to do:
        # define THE ID in the Header                   √
        # jme3 < << > >> fnode w7da                     √
        # jme3 -options m3a ay haja                     √
        # jme3 |                                        √
        # jme3 $ m3a ay haja mn gher space              √
        # jme3 = m3a koulchi mn gher space              √
        # jme3 & m3a &                                  
        -------------------------------------------------
        # find the shell and increment (tips : init env before the 69 while loop)

        # update lexer " '                              √ 
        # handle redirections errors


# the tree way:
                cmd | cmd -> split by pip
                - now we have two cmds lets split them again with espace
                cmd -ls -> splited by space
                now the tree looked like this:
                ------------------------------------------------------------------
                 *if there is pip:
                ------------------------------------------------------------------
                        [cmd]    [|]    [cmd]         -> now we have three ID's CMD and pip amd CMD 
                          |               |
                    [cmd] [opt]      [cmd] [opt]      -> now we have two ID in each node CMD and OPTION
                ------------------------------------------------------------------
                    *opt -> option
                ------------------------------------------------------------------
                 * if theres no pip:
                ------------------------------------------------------------------
                        [cmd] [option] -> directly splited by space
                ------------------------------------------------------------------



# to do next and update:
                create struct has those members:
                                                *cmd_value
                                                *options_tab>[500]
                                                *std_input
                                                *std_output
                                                *type

                update the lexer to dected which type of the cmd:
                                                if it HAS PIPE.  (if no then  next)
                                                if it HAS && or ||. (if no then next)
                                                if it HAS nothing. (final step)

                on which type we have we gonna give a specifc ID's and nodes and parsing.
                if has PIPE then we init the 

install greper help

<!-- to do next part 2 in parse-->
        check if the first is rederct or cmd
        delete the redrict
        do not handle simcolone ';'
        if we did the bonus handle '()'

************ segfault f ft_lexer ******************

command node :
        add input fd
        output fd
        red type
        stop word for heredoc


<!-- exuce part -->
        checking if the cmnds is exist
        find the priority
        create the files for rederctions
        if herdoc
        running the cmds
        free all
        removes the forbidden functions


to do youness

update lexer /
delete lexer unexpanded node
export
redirection
<!--  -->
< f lwel

>> >  flekher

# after redirection always a word a WORD <-------------------------------------------------------------------------->

# handle ( {} ) syntax errors

bash-3.2$ ls -la < $test
bash: $test: ambiguous redirect

<!----

> 1
< 2
>> 3
<< 4

---->



### WARNING
rak 9alb input and output dial > √


### SEGFAULT
whatever HOME




3ndk problem fe argument 3




### DELETE FORBBIDEN FUNC
### LEAKS
### UPDATE CD
### UPDATE ENV
### NORME


I allocate eof in data
when u r done with herdoc free data->eof with free_split command
everything is perfect
