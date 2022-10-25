fn main() {
    let r:Vec<i32> = vec![5, 6, 7];
    println!("{}", maximum(&r));
    println!("{}", volume(r));
    
}

fn volume(h: Vec<i32>) -> i32 {
        let n = h.len();

        // characterization of the histogram's variations (rising or falling edges)
        let mut edges:Vec<i32>  = vec![0;n]; 
        edges[0] = 1; edges[n-1] = -1; // convention outside of the histogram, earth level is negative
        for i in 1..n {
            edges[i] = h[i+1]-h[i]; // convention: *non-causal* discrete derivative
        }

        let mut capacity = 0;
        if n <= 2 || minimum(&edges) >= 0 || maximum(&edges) <= 0 {
            capacity = 0; // cas d'arrêt les plus simples
        }

        else if n > 2 {
            // characterization of the histogram's extrema
            let mut max_ant:Vec<i32> = vec![0;n]; // anterior max elevation
            let mut max_ult:Vec<i32> = vec![0;n]; // ulterior max elevation
            
            max_ant[0]   = h[0]; // max de {h[0]} = h[0]
            max_ult[n-1] = h[n-1]; // max de {h[n-1]} = h[n-1] 

            for i in 1..n {
                max_ant[i]     = std::cmp::max(max_ant[i-1], h[i]);
                max_ult[n-i-1] = std::cmp::max(max_ult[n-i], h[n-i]);
            }

            // Algo de décision et calcul de la capacité
            let mut ind_start = 0;
            while ind_start < n && edges[ind_start] > 0 {ind_start += 1;}
            let mut ind_stop = n-1;
            while ind_stop  > 0 && edges[ind_stop]  < 0 {ind_stop  -= 1;}
            
            for i in ind_start..ind_stop {
                capacity += std::cmp::min(max_ant[i], max_ant[i]) - h[i];
            }
        }
        return capacity;
    }


fn maximum(r:&Vec<i32>) -> i32 {
    let mut m = r[0];
    for i in 1..r.len() {
        if r[i] > m {
            m = r[i];
        };
    }
    return m;
}

fn minimum(r:&Vec<i32>) -> i32 {
    let mut m = r[0];
    for i in 1..r.len() {
        if r[i] < m {
            m = r[i];
        };
    }
    return m;
}