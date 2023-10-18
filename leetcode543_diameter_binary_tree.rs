// Definition for a binary tree node.
// #[derive(Debug, PartialEq, Eq)]
// pub struct TreeNode {
//   pub val: i32,
//   pub left: Option<Rc<RefCell<TreeNode>>>,
//   pub right: Option<Rc<RefCell<TreeNode>>>,
// }
// 
// impl TreeNode {
//   #[inline]
//   pub fn new(val: i32) -> Self {
//     TreeNode {
//       val,
//       left: None,
//       right: None
//     }
//   }
// }
use std::rc::Rc;
use std::cell::RefCell;
use std::cmp::max; // added
type Node = Option<Rc<RefCell<TreeNode>>>; // added

impl Solution {
    pub fn diameter_of_binary_tree(root: Node) -> i32 {
        let (depth, diam): (i32,i32) = Self::dfs(&root);
        return diam;
    }

    pub fn dfs(root: &Node) -> (i32, i32) {
        match root {
            None => {(0, 0)}
            Some(node) => {
                let (depth_L, diam_L): (i32, i32) = Self::dfs(&node.borrow().left);
                let (depth_R, diam_R): (i32, i32) = Self::dfs(&node.borrow().right);
                let diam_max_LR: i32 = max(diam_L, diam_R);
                (i32::max(depth_L, depth_R) + 1, i32::max(diam_max_LR, depth_L + depth_R))
            }
        }
    }

}