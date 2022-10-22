fn main () -> () {
    let nums: [i32; 4] = [2,7,11,15];
    let target: i32 = 9;
    let sm: (i32, i32) = twosums(&nums,&target);
    println!("les deux indices sont {}, {}", sm.0, sm.1);
}


fn twosums(vec: &[i32], target: &i32) -> (i32,i32) {
    let lv = vec.len();
    for ind1 in 1..=lv {
        for ind2 in (ind1+1)..=lv {
            if vec[ind1] + vec[ind2] == *target {
                return (ind1,ind2)
            }
        }
    }
    return (1,2)
}

