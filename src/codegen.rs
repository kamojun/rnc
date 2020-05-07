use crate::parse::Node;
use crate::parse::NodeKind::*;

fn gen(node: &Node) {
    if let Some(val) = node.if_num() {
        println!("  push {}", val);
    } else if node.is_lvar() {
        gen_lval(node);
        println!("  pop rax");
        println!("  mov rax, [rax]");
        println!("  push rax");
    } else if let Node::Bin {
        kind: NdAssign,
        lhs,
        rhs,
    } = node
    {
        gen_lval(lhs);
        gen(rhs);
        println!("  pop rdi");
        println!("  pop rax");
        println!("  mov [rax], rdi");
        println!("  push rdi");
    } else if let Node::Bin { kind, lhs, rhs } = node {
        gen(lhs);
        gen(rhs);
        println!("  pop rdi");
        println!("  pop rax");
        let code = match kind {
            NdAdd => "  add rax, rdi",
            NdSub => "  sub rax, rdi",
            NdMul => "  imul rax, rdi",
            NdDiv => "  cqo\n  idiv rdi",
            NdEq => "  cmp rax, rdi\n  sete al\n  movzb rax, al", // 最後のmovzbは、raxの上位56を削除して、下位8ビットにalを入れるということだろう。
            NdNeq => "  cmp rax, rdi\n  setne al\n  movzb rax, al",
            NdLt => "  cmp rax, rdi\n  setl al\n  movzb rax, al",
            NdLe => "  cmp rax, rdi\n  setle al\n  movzb rax, al",
            _ => unimplemented!(),
        };
        println!("{}", code);
        println!("  push rax")
    }
    println!("");
}
fn gen_lval(node: &Node) {
    println!("  mov rax, rbp");
    println!("  sub rax, {}", node.offset());
    println!("  push rax\n");
}
pub fn code_gen(nodes: Vec<Node>) {
    const HEADER: &str = ".intel_syntax noprefix\n.global main\nmain:";
    // まず現在の関数のrbpをスタックにpush(戻る場所)、次に現在のrsp(スタックポインタ)の値をrbpに格納し、rspを使用する変数分ずらす
    println!("{}", HEADER);
    println!("  push rbp"); // まず現在の関数のrbpをスタックにpush(戻る場所?)
    println!("  mov rbp, rsp"); // 次にrbpに現在のrspを入れる。rspは常にスタックの1番下を指していて、rbpもそこを指すようになる
    println!("  sub rsp, 26*8"); // rspを変数分ずらす。この時スタックは自動的にずれる。(26回pushするのと同じ?)
    for node in &nodes {
        gen(node);
        println!("  pop rax");
    }
    println!("  mov rsp, rbp");
    println!("  pop rbp");
    println!("  ret");
}

use std::fs;
use std::io;
use std::io::{BufWriter, Write};
pub fn print_graph(node: &Node) -> io::Result<()> {
    let mut f = BufWriter::new(fs::File::create("graph.dot").unwrap());
    f.write(
        b"digraph {
node [
style = \"filled\",
fontsize = 16,
fillcolor = \"green\",
];
",
    )?;
    f.write(graph_gen(node, "root".to_owned()).as_bytes())?;
    f.write(b"}\n")?;
    Ok(())
}
pub fn graph_gen(node: &Node, name: String) -> String {
    if let Node::Leaf { val, kind, offset } = node {
        match kind {
            NdNum => format!("{} [label=\"{:?} {}\"];\n", name, kind, val),
            NdLvar => format!("{} [label=\"{:?} {}\"];\n", name, kind, offset),
            _ => panic!(),
        }
    } else if let Node::Bin { kind, lhs, rhs } = node {
        let mut s = format!("{} [label=\"{:?}\"];\n", name, kind);
        let left = format!("{}l", name);
        let right = format!("{}r", name);
        s = s + &graph_gen(lhs, left.clone()) + &graph_gen(rhs, right.clone());
        s = s + &format!("{} -> {} [];\n{} -> {} [];\n", name, left, name, right);
        s
    } else {
        unimplemented!();
    }
}
