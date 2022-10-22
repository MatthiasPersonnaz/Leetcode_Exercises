fn main() {
    let nums: [i32; 10] = [-5, -5, -12, -3, -4, -1, -2, -3, -2, 1];

    let sm: i32 = smallest_missing(&nums);
    println!("it is {sm}");
}

fn smallest_missing(l: &[i32]) -> i32 {
    let mx: i32 = *l.iter().max().unwrap();
    if mx <= 0 { return 1; }
    for cand in 1..=mx {
        if !l.contains(&cand) {
            return cand;
        }
    }
    mx + 1
}