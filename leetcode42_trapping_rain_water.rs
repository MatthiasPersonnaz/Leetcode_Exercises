fn main() {
    let r:Vec<i32> = vec![1, 2, 3, 4, 5, 2, 7, 2, 18, 17, 14, 20];
    let r:Vec<i32> = vec![0,1,0,2,1,0,1,3,2,1,2,1]; // réponse 6
    let r:Vec<i32> = vec![4,2,0,3,2,5]; // réponse 9
    println!("total volume = {}", volume(r));
}

fn volume(h: Vec<i32>) -> i32 {
        let n:usize = h.len();
        

        // characterization of the histogram's variations (rising or falling deriv)
        let mut deriv:Vec<i32>  = vec![0;n];
        for i in 0..n-1 {
            deriv[i] = h[i+1]-h[i]; // convention: *non-causal* discrete derivative
        }
        deriv[n-1] = -1; // convention outside of the histogram: earth level is negative
        


        let mut capacity_t = 0;
        let mut capacity_v:Vec<i32> = vec![0;n];

        if n <= 2 || minimum(&deriv) >= 0 || maximum(&deriv) <= 0 {
            capacity_t = 0; // cas d'arrêt les plus simples
        }
        

        else {
            // characterization of the histogram's extrema
            let mut max_ant:Vec<i32> = vec![0;n]; // anterior max elevation
            let mut max_ult:Vec<i32> = vec![0;n]; // ulterior max elevation
            
            max_ant[0]   = h[0];   // max {h[0]}   = h[0]
            max_ult[n-1] = h[n-1]; // max {h[n-1]} = h[n-1] 

            for i in 1..n {
                max_ant[i]     = std::cmp::max(max_ant[i-1], h[i]);
                max_ult[n-i-1] = std::cmp::max(max_ult[n-i], h[n-i-1]);
                //              max juste après ----------^^^         ^^^^^--- hauteur courante
            }



            // calcul de la capacité
            let mut ind_start:usize = 0;
            while ind_start < n && deriv[ind_start] >= 0 {ind_start += 1;}
            
            let mut ind_stop:usize  = n-1;
            while ind_stop  > 0 && deriv[ind_stop]  <= 0 {ind_stop  -= 1;}
            
            for i in ind_start..ind_stop+1 {
                let ac = std::cmp::min(max_ant[i], max_ult[i]) - h[i];
                capacity_t += ac;
                capacity_v[i] = ac;
            }

            println!("{:?}, deriv", deriv);
            println!("{:?}, max_ant", max_ant);
            println!("{:?}, max_ult", max_ult);
            println!("{:?}, histo", h);
            println!("{:?}, capa", capacity_v);
        }
        return capacity_t;
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


// FORMATAGE LEETCODE
impl Solution {
    pub fn trap(h: Vec<i32>) -> i32 {
        let n:usize = h.len();
        
        // characterization of the histogram's variations (rising or falling deriv)
        let mut deriv:Vec<i32>  = vec![0;n];
        for i in 0..n-1 {
            deriv[i] = h[i+1]-h[i]; // convention: *non-causal* discrete derivative
        }
        deriv[n-1] = -1; // convention outside of the histogram: earth level is negative
        


        let mut capacity_t = 0;
        let mut capacity_v:Vec<i32> = vec![0;n];

        if n <= 2 || Solution::minimum(&deriv) >= 0 || Solution::maximum(&deriv) <= 0 {
            capacity_t = 0; // cas d'arrêt les plus simples
        }
        

        else {
            // characterization of the histogram's extrema
            let mut max_ant:Vec<i32> = vec![0;n]; // anterior max elevation
            let mut max_ult:Vec<i32> = vec![0;n]; // ulterior max elevation
            
            max_ant[0]   = h[0];   // max {h[0]}   = h[0]
            max_ult[n-1] = h[n-1]; // max {h[n-1]} = h[n-1] 

            for i in 1..n {
                max_ant[i]     = std::cmp::max(max_ant[i-1], h[i]);
                max_ult[n-i-1] = std::cmp::max(max_ult[n-i], h[n-i-1]);
                //              max juste après ----------^^^         ^^^^^--- hauteur courante
            }



            // calcul de la capacité
            let mut ind_start:usize = 0;
            while ind_start < n && deriv[ind_start] >= 0 {ind_start += 1;}
            
            let mut ind_stop:usize  = n-1;
            while ind_stop  > 0 && deriv[ind_stop]  <= 0 {ind_stop  -= 1;}
            
            for i in ind_start..ind_stop+1 {
                let ac = std::cmp::min(max_ant[i], max_ult[i]) - h[i];
                capacity_t += ac;
                capacity_v[i] = ac;
            }

            println!("{:?}, deriv", deriv);
            println!("{:?}, max_ant", max_ant);
            println!("{:?}, max_ult", max_ult);
            println!("{:?}, histo", h);
            println!("{:?}, capa", capacity_v);
        }
        return capacity_t;
    }
    
    pub fn maximum(r:&Vec<i32>) -> i32 {
        let mut m = r[0];
        for i in 1..r.len() {
            if r[i] > m {
                m = r[i];
            };
            }
        return m;
        }

    pub fn minimum(r:&Vec<i32>) -> i32 {
        let mut m = r[0];
        for i in 1..r.len() {
            if r[i] < m {
                m = r[i];
            };
        }
        return m;
    }
}