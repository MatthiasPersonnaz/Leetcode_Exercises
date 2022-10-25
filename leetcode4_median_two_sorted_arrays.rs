fn main() {
    let nums1: Vec<i32> = vec![3,6];
    let nums2: Vec<i32> = vec![5,7];

    let mut merged: Vec<i32> = nums1.clone();
    merged.extend(nums2.clone());
    merged.sort();
    let total_len: usize = merged.len();
    let answer: f64;
    if total_len % 2 == 1 {
        answer = merged[total_len/2] as f64;
    }
    else {
        answer = (merged[total_len/2 - 1] as f64 + merged[total_len/2] as f64) / 2.;
    }

    println!("answer is {answer:.1}");
    let computed: f64 = find_median_sorted_arrays(nums1, nums2);
    println!("computed is {computed:.1}");
}

fn find_median_sorted_arrays(nums1: Vec<i32>, nums2: Vec<i32>) -> f64 {

    let m: usize = nums1.len();
    let n: usize = nums2.len();

    let mid1: usize = m / 2;
    let mid2: usize = n / 2;

    println!("nums1={nums1:?} {}", nums1[mid1]);
    println!("nums2={nums2:?} {}\n", nums2[mid2]);

    if (m == 1) & (n == 2) {
        let x: i32 = nums1[0];
        if x <= nums2[0] { return nums2[0] as f64; }
        if x >= nums2[1] { return nums2[1] as f64; }
        else { return x as f64; }
    }

    if (m == 2) & (n == 1) {
        let x: i32 = nums2[0];
        if x <= nums1[0] { return nums1[0] as f64; }
        if x >= nums1[1] { return nums1[1] as f64; }
        else { return x as f64; }
    }

    if (m == 2) & (n == 2) {
        let a: i32 = nums1[0];
        let b: i32 = nums1[1];
        let c: i32 = nums2[0];
        let d: i32 = nums2[1];
        
        if a <= c {
            if b >= d {
                return (c as f64 + d as f64) / 2.;
            }
            else {
                return (b as f64 + c as f64) / 2.;
            }
        }
        else { // c <= a
            if d >= b {
                return (a as f64 + b as f64) / 2.;
            }
            else {
                return (a as f64 + d as f64) / 2.;
            }
        }

    }

    if (m == 1) & (n > 2) {
        let x: i32 = nums1[0];
        return aux(nums2, x);
    }
    if (m > 2) & (n == 1) {
        let x: i32 = nums2[0];
        return aux(nums1, x);
    }
    
    if nums1[mid1] < nums2[mid2] {
        return find_median_sorted_arrays(nums1[mid1..].to_vec(),
                                         nums2[..=mid2].to_vec());
    }
    else if nums1[mid1] > nums2[mid2] {
        return find_median_sorted_arrays(nums1[..=mid1].to_vec(),
                                         nums2[mid2..].to_vec());
    }
    else {
        if (m%2 == 0) & (n%2 == 0) {
            let mx: i32 = std::cmp::max(nums1[mid1-1], nums2[mid2-1]);
            return (mx as f64 + nums1[mid1] as f64) / 2.;
        }
        else {
            return nums1[mid1] as f64;
        }
    }

}

fn aux(nums: Vec<i32>, x: i32) -> f64 {
    let len: usize = nums.len();
    let mid: usize = len / 2;
    let piv: i32 = nums[mid];

    if len%2 == 1 {
        if x == piv { return x as f64; }
        else if (x > piv) & (x >= nums[mid+1]) {
            return (piv as f64 + nums[mid+1] as f64) / 2.;
        }
        else if (x > piv) & (x <= nums[mid+1]) {
            return (piv as f64 + x as f64) / 2.;
        }
        else if (x < piv) & (x <= nums[mid-1]) {
            return (piv as f64 + nums[mid-1] as f64) / 2.;
        }
        else { // (x < piv) & (x >= nums[mid-1])
            return (piv as f64 + x as f64) / 2.;
        }
    }

    else { // len%2 == 0
        if x == piv { return x as f64; }
        else if (x < piv) & (x >= nums[mid-1]) { return x as f64; }
        else if (x < piv) & (x <= nums[mid-1]) { return nums[mid-1] as f64; }
        else { return piv as f64; } // x > piv
    }
}
