type token = OpenBrace
           | CloseBrace
           | OpenParen
           | CloseParen
           | Semicolon
           | Keyword of string
           | Identifier
           | Integer of int;;

open Batteries

let rec lex tokens =
    match tokens with
    | [] -> []
    | "{"::ts -> OpenBrace::(lex ts)
    | "}"::ts -> CloseBrace::(lex ts)
    | "("::ts -> OpenParen::(lex ts)
    | ")"::ts -> CloseParen::(lex ts)
    | ";"::ts -> Semicolon::(lex ts)
    | t::ts ->
    (
        if Char.is_whitespace t then lex ts else lex_const_or_id tokens
    )