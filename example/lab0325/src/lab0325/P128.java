package lab0325;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;

public class P128 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		BufferedReader in;
		FileWriter out;

		int testNum;
		String infix;
		String postfix ="";

		int i,j,k; 

		String path = P128.class.getResource("").getPath(); 
		try {
			in = new BufferedReader(new FileReader(path+"input_P128.txt"));
			out = new FileWriter("output_P128.txt");

			testNum = Integer.valueOf(in.readLine());
			for(k =0; k < testNum; k ++){

				infix = in.readLine();

				out.write("#"+(k+1)+" ");

				PostOrder postorder = new PostOrder();

				postfix = postorder.postChange(infix);

				System.out.println("���� ��ȸ : "+ postfix);
				out.write(postfix + "\r\n");


				System.out.println("���~~ : "+ postorder.cal_postfix(postfix));
			}
			in.close();
			out.close();

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}


//		int a = 30;
//		int b = '+'; // 43�ϰ�?
//
//		System.out.println("73�̿���~~~\n\n");
//		System.out.println(a+b);
//		System.out.printf("%c\n",a+b);
//
//		// �迭 �ʱ�ȭ ������ ��, 
//		int blar[] = new int[3];
//
//		System.out.println(blar[2]);
//		System.out.printf("%c",blar[2]); // NULL
		
		

	}

}


class PostOrder{

	int stack[] = new int[50];
	// �������� �Է��� ���� ������ ����.
	int stackTop = -1;


	int pop(){
		if(stackTop < 0){
			System.out.println("stack underflow!!");
			return 1;
		}
		return stack[stackTop--];
	}
	int push(int item){
		// idx 49������ ���� �� �ְ� 50���� ���� �� ����. 
		if(stackTop >=  50-1 ){
			System.out.println("stack overflow!!");
			return 1;
		}
		stack[++stackTop] = item;

		// ���� item ��ȯ�ϴ� ������ ����
		return item;
	}
	// �� ��� �̸��� ������?? peek
	int getStackTop(){
		if(stackTop < 0)
			return -1;
		else
			return stack[stackTop];
	}

	boolean isStackEmpty(){
		// �̰� ��ü�� ���ǾƴϿ�??? �׷� false, true�� �䳪���±���.
		// stackTop < 0 �϶� true ��ȯ...
		return (stackTop < 0);
	}

	// op �� int�� ��ҳ�. '+'�� int�� ��?? �Ƹ� �ƽ�Ű�ϱ� 43 �̳�? ����
	boolean isOperator(int op){
		return op =='+' || op == '-' || op == '*' || op == '/';
	}



	int precedence(int op){
		switch(op){
		case '(':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
			// default ����??	
			// ��� ����� ���� �ƴ� ��,
		default:
			return 3;
		}
	}

	String postChange(String src){

		stackTop = -1;
		int idx = 0;

		String dst = new String();
		// 0 ... to length -1 

		while(src.length() -1 >= idx){

			if(src.charAt(idx) == '('){
				// int ����ȯ �ʿ��Ѱ�??? op �κп����� ������ �� ������
				push( (src.charAt(idx)) );
				idx ++;

			} else if( src.charAt(idx) == ')'){

				while(getStackTop() != '('){
					dst += ((char)pop());
					dst += ' ';
				}
				pop();
				idx++;

			} else if( isOperator(src.charAt(idx))){

				// �ֻ��� ���� ��ҿ�, ��� ���� idx�� operator �켱���� ��..
				// �ֻ��� ���� ��Ұ� �켱������ ���� �� ����Ǵ� ��ƾ.
				while( ! isStackEmpty() && precedence(getStackTop()) >= precedence(src.charAt(idx)) ){

					dst += ((char)pop());
					dst += ' ';
				}
				push(src.charAt(idx));
				idx ++;

			} else if( src.charAt(idx) >= '0' && src.charAt(idx) <= '9' ){

				// �� �ݺ��� ����??
				do{
					dst += src.charAt(idx);
					idx ++;
					// �ҽ��� �Ǹ����� ���� ���ٸ�?
					if(src.length() == idx)
						break;
				}while( src.charAt(idx) >= '0' && src.charAt(idx) <= '9');

				dst += ' ';
			} else {
				// ��� ������ �ƴҶ�,, ��� ������ �ƴҶ��� �ֳ�.
				System.out.println("�� ���� ����� �� �ֳ�??"); // ����� �� ����.
				idx++;

			}
		}

		// ������ ���� �ʾҴٸ�, �������� pop �ض�. �Ǹ��������ڳ� �ѹ�����.
		while (!isStackEmpty()){
			dst += ((char)pop());
			System.out.println("���� �����ڸ� ~~ pop�ϴ� ��� : "+ dst.charAt(dst.length()-1));
			dst += ' ';
		}
		return dst;
	}

	int cal_postfix(String src){

		int idx = 0;
		while( src.length() -1 >= idx ){

			// ���ڶ�� �� �� ��ü push(�� �ڸ�) 
			// �� �ڸ� �ִ� �� ��ȿ�� ���ΰ� ������, �ѱ�¥�� 49 20 �̷���... �׷��� �ȵǴ±���. 4 9 2 0 ���������ϸ� ������ �ȵ�
			// �ٲ�ߵȴ�. ' '�� �������� 
			if( src.charAt(idx) >= '0' && src.charAt(idx) <= '9' ){

				// ������ ' '���� �Ǵ�����. ������ �����̸� ���ڸ� ���ڶ�¸��̴ϱ� �־����
				if( src.charAt(idx +1) == ' ' ){
					push((src.charAt(idx)-48));
					idx += 2;
					// ������ �Ƹ� �����̰���. ������ �˾Ƽ� ó���ϴ� ��ƾ ������.
					// �ƴ� ���� ���� ��ĭ �� idx++�� ��ų��.. �׷�����
				}else if( src.charAt(idx+1) >= '0' && src.charAt(idx+1) <= '9'){
					int temp = (src.charAt(idx)-48)*10 + (src.charAt(idx)-48);
					push(temp); //���ڸ����ڳִ°ǵ�.. ���� �������.
					idx += 3;
				}
				// �������϶� ����~
			} else if ( isOperator(src.charAt(idx)) ){
				int val2 = pop();
				int val1 = pop();
				
//				System.out.println("scr.charAt : " +src.charAt(idx));
//				System.out.println("val1 : "+val1 + " val2 : "+val2);
				int result = 123; 

				// val1 +-*/ val2 �� �� push..
				switch( src.charAt(idx) ){
				case '+':
					result = val1 + val2;
					break;
				case '-':
					result = val1 - val2;
					break;
				case '*':
					result = val1 * val2;
					break;
				case '/':
					result = val1 / val2;
					break;
				
				}
//				System.out.println("result: " +result);
				idx += 2;
				push(result);

			}

		}
		
		return pop();
		
	}

}



