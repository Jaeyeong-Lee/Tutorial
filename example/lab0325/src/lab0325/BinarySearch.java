package lab0325;

import java.util.Scanner;

public class BinarySearch {

//	public static void main(String[] args) {
//		// TODO Auto-generated method stub
//
//		Scanner sc = new Scanner(System.in);
//		
//		int c = sc.nextInt();
//		int item[] = new int[c];	// c=5..
//		String[] array = new String[c];
//		
//		/*
//		for(int i = 0; i< item.length; i++)
//			item[i] = sc.nextInt();
//		*/
//		for(int i = 0; i< c; i++){
//			
//			array[i] = sc.next();
//		}
//		
//		for(int i = 0; i< item.length; i++)
//			System.out.print(item[i]+" ");
//		
//		
//		BSTree bst = new BSTree();
//		/*
//		for(int i = 0; i< item.length; i++)
//			bst.insertBST(item[i]);
//		*/
//		
//		for(int i = 0; i < array.length; i++){
//			bst.insertBST(array[i].charAt(0));
//		}
//		bst.printBST();
//		// 왜 root.data 가 0이지?? 0아닌데,, 
//		
//		bst.printRootdata();
//	}

}

class TreeNode{
	char data;
	TreeNode left;
	TreeNode right;
}

class BSTree{
	
	private TreeNode root = new TreeNode();
	
	public TreeNode insertKey ( TreeNode root, char x){
		
		TreeNode p = root;
		TreeNode newNode = new TreeNode();
		
		newNode.data = x;
		newNode.left = null;
		newNode.right = null;
		
		// p == null 무슨 의미지?? 메모리가 없다?
		// 아니아니 루트 노드가 없으면 자기가 루트노드가 되라는 말.
		if(p == null)
			return newNode;
		else if( newNode.data < p.data ){
			p.left = insertKey(p.left,x);
			return p;
		}else if (newNode.data > p.data){
			p.right = insertKey(p.right,x);
			return p;
		}
		else return p;
		
		
		
	}
	
	
	public void insertBST(char x){
		root = insertKey(root,x);
	}
	
	public void inorder(TreeNode root){
		if(root != null){
			inorder(root.left);
			System.out.print(root.data +" ");
			inorder(root.right);
		}
		
	}
	public void printBST(){
		inorder(root);
		System.out.println();
	}
	public void printRootdata(){
		System.out.println(root.data);
	}
}