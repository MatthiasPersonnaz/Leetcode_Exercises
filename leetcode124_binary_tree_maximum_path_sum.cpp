/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        return cutChoice(root);
    }

    int cascadePathFinding(TreeNode* tree) {
        if (tree == nullptr) {return 0;}
        return tree->val + max(cascadePathFinding(tree->left), cascadePathFinding(tree->right));
    }

    int cutChoice(TreeNode* tree) {
        if (tree == nullptr) {return INT_MIN;}
        int indepPathL = cutChoice(tree->left);
        int indepPathR = cutChoice(tree->right);

        int cascadeL = cascadePathFinding(tree->left);  // path exists standalone in the LEFT  child tree starting from its root
        int cascadeR = cascadePathFinding(tree->right); // path exists standalone in the RIGHT child tree starting from its root

        int indepPathSide = max(indepPathL, indepPathR); // path exists standalone in ONLY 1 of the children trees

        int maxOneSide = max(cascadeL, cascadeR); // path includes root and continues in ONLY 1 of the children trees
        int maxBothSides = tree->val + max(maxOneSide, cascadeL + cascadeR); // path includes root and continues potentially in ONE or BOTH children trees
        int maxIncludeRoot =  max(indepPathSide, maxBothSides);
        int maxIncludeRootandContinues = max(maxIncludeRoot, indepPathSide);


        return max(maxIncludeRootandContinues, tree->val);
        // include case the path is just the root itself (does not continue in NEITHER of the children)
    }
};

