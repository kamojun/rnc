use std::env;
extern crate getopts;
use getopts::Options;

mod codegen;
mod ctype;
mod err;
mod parse;
mod tokenize;
mod util;
use crate::codegen::{code_gen, print_graph};
use crate::err::*;
use crate::parse::*;
use crate::tokenize::*;

/// エラー終了時には終了ステータス1となる(Result型を返すため)
fn main() -> Result<(), String> {
    let args: Vec<String> = env::args().collect();

    // コマンドラインオプション
    let mut opts = Options::new();
    opts.optflag("t", "", "print token list and types");
    opts.optflag("g", "", "print node graph");
    let matches = match opts.parse(&args[1..args.len()]) {
        // コマンドライン引数の先頭と末尾はオプションではない
        Ok(m) => m,
        Err(f) => Err(f.to_string())?,
    };

    match env::args().last() {
        Some(filename) => {
            println!(".file 1 \"{}\"", filename);
            let code = open(&filename).map_err(|_| format!("cannot open file {}", filename))?;
            match compile(&code, matches.opt_present("t"), matches.opt_present("g")) {
                Err(CompileError::Tokenize { pos, msg }) => error_at(&code, pos, msg, &filename),
                Err(CompileError::Parse { pos, msg }) => {
                    error_at(&code, pos, format!("parse failed: {}", msg,), &filename)
                }
                Err(CompileError::CodeGen { msg, pos }) => {
                    error_at(&code, pos, format!("codegen failed: {}", msg,), &filename)
                }
                _ => Ok(()),
            }
        }
        None => error("input needed"),
    }
}

fn compile(code: &String, print_tklist: bool, print_graph_: bool) -> Result<(), CompileError> {
    // トークナイズ
    let token_list = Lexer::new(code).tokenize()?;
    if print_tklist {
        for tk in &token_list {
            println!("{:?}", tk);
        }
    }

    // パース
    let parser = Parser::new(&token_list, code.split('\n').collect());
    let (functions, globals, string_literals, types) = parser.program()?;
    if print_graph_ {
        print_graph(&functions);
    }
    if print_tklist {
        println!("{:?}", types);
    }

    // アセンブリコード生成
    code_gen(functions, globals, string_literals, token_list, types)?;
    Ok(())
}

use std::fs::File;
use std::io::prelude::*;
fn open(filename: &String) -> std::io::Result<String> {
    let mut file = File::open(filename)?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    if contents.chars().last() != Some('\n') {
        contents.push('\n');
    }
    Ok(contents)
}
