<h1>The First Step</h1>
1. The first step was making a very simple version of shell.<br>
  A while loop that keeps asking for input until you type 'exit'<br>
  <ul>
    <li>Print a PromptString(PS) e.g "&gt;", "$".</li>
    <li>Read a line of input (get_next_line):<br>
      cmd = get_next_line()<br>
      if (cmd == exit) break;<br>
      else printf(cmd);
    </li>
  </ul>
  <p>I made some changed on top of get_next_line to be able to detect escape characters so I can keep reading input even if I press enter after an imput like: "abc \", "\"...</p>


<h1>What's Next?</h1>
Now that we can read a command line, Logically the next step would be to execute the command line or atleast a very basic command. but first we need to understand what is a command.<br><br>

A basic command consists of a list of words separated by whitespaces.<br>
The first word is the command name(mandatory), the other words are optional(arguments)<br>
  <code>ls -l</code> <code>gcc shell.c -o sh</code> ...
  <br><br>
  To be able to execute a command we need to:
  <ol>
    <li>Scan input character by character to get tokens (Lexical Scanner)</li>
    <li>Extract input tokens (Tokenizer)</li>
    <li>Parse the tokens and create an AST (Parser)</li>
  </ol>

  <h2>1. Lexical Scanner:</h2>
  We need to read our input one character at a time so we can identify the characters that can be part of the token and those that are delimiter characters. Delimiter characters are the marks of the end of a token and they can be <b>whitespaces, `;`, `&`, ...</b><br><br>
  
  To easily be able to move around the input for lexical analysis, I created some helper functions to:
  <ul>
    <li>Retrieve the next character from input. <code>next_char();</code></li>
    <li>Return the last character we've read back to input. <code>unget_char();</code></li>
    <li>Look ahead (peek) to check the next character without returning it. <code>peek_char();</code></li>
    <li>Skip over whitespace characters. <code>skip_whitespace();</code></li>
  </ul>
  And to make the job easier, instead of passing the input directly to the scanner, I created a struct `t_cli` that will have a copy of our input and its length and the cursor position. So each time I have some job for the input I use that `t_cli`

  <div>
  <h2>2. Tokenizing Input:</h2>
  <p>Now we'll use the Scanner functions to extract input tokens</p>
  <ul>
    <li>I started by defining a struct to hold a single token <code>t_token</code> which will hold the input, size of input, and token text.</li>
    <li>Write the tokenize function which will retrieve the next token from input for that I need some helper functions and a helper struct to hold our token and it's size and it's index.</li>
    <ul>
      <li><code>add_to_buff()</code>: adds a single character to the token buffer</li>
      <li><code>create_token()</code>: convert a string to a token AKA <code>t_token</code></li>
      <li><code>free_token()</code></li>
      <li><code>tokenize()</code>: uses the previous helper function to initialize our token, keep retrieving next char until we reach an end of a delimiter, and we got our first token, keep doing that and we get all tokens</li>
    </ul>
  </ul>

  <h2>3. Parse The Tokens:</h2>
  <p>
  This part will use the lexical scanner functions to retrieve tokens and construct the AST that will be passed to the executor.
  For now the parser is one command called <code>execc</code>
  </p>
  
  
  
  
  <h2> In Progress... </h2>
</div>
