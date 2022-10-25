// matthias, work in progress
fn trap(h: Vec<i32>) -> i32 {
        let n = h.len();
        let mut capa: Vec<i32> = Vec::with_capacity(n+1); // cumulative capacity
        let mut fmel: Vec<i32> = Vec::with_capacity(n+1); // former max elevation
        let mut prev_max_elev: i32 = h[0];
        capa[0] = 0; // la première case ne contiendra jamais d'eau car il n'y a pas de cloison sur l'axe x=0
        let max_height = h.max();
        for i in 1..n-1 do {
            cur_height
        }
        return 6;