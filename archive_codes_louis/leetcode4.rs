fn main() {
    let nums1: Vec<i32> = vec![1,2,3,4,4,5,5,7,8];
    let nums2: Vec<i32> = vec![5];

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

    if m == 1 {
        return find_median_sorted_arrays
    }
    if n == 1 {
        let x: i32 = nums2[0];
        let piv: i32 = nums1[mid1];
        if m%2 == 1 {
            if x == piv { return x; }
        }
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
