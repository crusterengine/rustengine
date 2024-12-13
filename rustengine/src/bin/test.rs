// fn two_scopes() { //The first scope starts

//     for (0..5) { //The second scope starts

//     let mut my_string = String::From("Hallo");
//     my_string.add(itr)
//     print

//     } //The second scope ends here

// } //The first scope ends here, all variables becomes invalid.

// fn other_function (x: String) -> String{

//     return x + " extra text";

//     printen!("hi again");
// }

// fn two_scopes() { //The first scope starts

//     for i in 0..5 { //The second scope starts

//         let my_string = String::from("Hallo");

//     } //The second scope ends

// } //The first scope ends here, all variables becomes invalid.

// fn main() {
// two_scopes();
// let mystrign = String::from("hallo");
// let returned_string = other_functio2(mystrign);

// print!("{}", returned_string);
// //print!("{}", mystrign);

// }

// fn main() {

//     let s = String::from("hello");
//     let r1 = &s; // Immutable reference
//     print!("{}, {}", s, r1);
// }

// fn main (){

//     let s1 = String::from("hello");
//     let s2 = s1;

// }

fn edit(s: &mut String) {
    s.push_str(" !");
}

fn main() {
    // let mut my_string = String::from("hello hanne");
    // edit(&mut my_string);
    // println!("{}", my_string);


    // let subsection_of_my_string = &my_string[0..1];
    // print!("{}", subsection_of_my_string)

    let ins = Some(5);
    let inf = None;

    let result1 = add_one(ins);
    let result2 = add_one(inf);

    println!("with some: {}", result1);
    println!("with none: {}", result2);


}

fn add_one (i: Option<i32>) -> i32{

    match i {
        Some(x) => x+1,
        None => 0+1,
    }

}
