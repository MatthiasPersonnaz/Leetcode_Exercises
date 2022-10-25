fn main() {
    let r:Vec<i32> = vec![5, 6, 7];
    println!("{}", trap(r));
}

fn trap(h: Vec<i32>) -> i32 {
        let n = h.len();
        let max_height = maximum(&h);

        let mut capa: Vec<i32> = Vec::with_capacity(n+1); // cumulative capacity
        let mut pmel: Vec<i32> = Vec::with_capacity(n+1); // previous max elevation

        capa[0] = 0; // la première case ne contiendra jamais d'eau car il n'y a pas de cloison sur l'axe x=0
        pmel[0] = h[0]; // max de {h[0]} = h[0]
        for i in 1..(n-1) {
            pmel[i] = std::cmp::max(pmel[i-1],h[i]);
        }
        return 6;
    }


fn maximum(r:&Vec<i32>) -> i32 {

    let mut m = r[0];
    for i in 1..5 {
        if r[i] > m {
            m = r[i];
        };
    }
    return m;
}