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

				System.out.println("후위 순회 : "+ postfix);
				out.write(postfix + "\r\n");


				System.out.println("결과~~ : "+ postorder.cal_postfix(postfix));
			}
			in.close();
			out.close();

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}


//		int a = 30;
//		int b = '+'; // 43일것?
//
//		System.out.println("73이여야~~~\n\n");
//		System.out.println(a+b);
//		System.out.printf("%c\n",a+b);
//
//		// 배열 초기화 안했을 때, 
//		int blar[] = new int[3];
//
//		System.out.println(blar[2]);
//		System.out.printf("%c",blar[2]); // NULL
		
		

	}

}


class PostOrder{

	int stack[] = new int[50];
	// 마지막에 입력한 값을 저장할 변수.
	int stackTop = -1;


	int pop(){
		if(stackTop < 0){
			System.out.println("stack underflow!!");
			return 1;
		}
		return stack[stackTop--];
	}
	int push(int item){
		// idx 49까지는 넣을 수 있고 50부터 넣을 수 없다. 
		if(stackTop >=  50-1 ){
			System.out.println("stack overflow!!");
			return 1;
		}
		stack[++stackTop] = item;

		// 굳이 item 반환하는 이유가 뭐지
		return item;
	}
	// 이 기능 이름이 뭐더라?? peek
	int getStackTop(){
		if(stackTop < 0)
			return -1;
		else
			return stack[stackTop];
	}

	boolean isStackEmpty(){
		// 이거 자체가 조건아니여??? 그래 false, true로 답나오는구나.
		// stackTop < 0 일때 true 반환...
		return (stackTop < 0);
	}

	// op 값 int에 담았네. '+'이 int로 몇?? 아마 아스키니깐 43 이냐? ㅇㅇ
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
			// default 머지??	
			// 모든 경우의 수가 아닐 때,
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
				// int 형변환 필요한가??? op 부분에서도 문제될 거 같은데
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

				// 최상위 스택 요소와, 방금 꺼낸 idx의 operator 우선순위 비교..
				// 최상위 스택 요소가 우선순위가 높을 때 수행되는 루틴.
				while( ! isStackEmpty() && precedence(getStackTop()) >= precedence(src.charAt(idx)) ){

					dst += ((char)pop());
					dst += ' ';
				}
				push(src.charAt(idx));
				idx ++;

			} else if( src.charAt(idx) >= '0' && src.charAt(idx) <= '9' ){

				// 이 반복문 뭐지??
				do{
					dst += src.charAt(idx);
					idx ++;
					// 소스의 맨마지막 까지 갔다면?
					if(src.length() == idx)
						break;
				}while( src.charAt(idx) >= '0' && src.charAt(idx) <= '9');

				dst += ' ';
			} else {
				// 모든 조건이 아닐때,, 모든 조건이 아닐때도 있나.
				System.out.println("이 문장 수행된 적 있나??"); // 수행된 적 없다.
				idx++;

			}
		}

		// 스택이 비지 않았다면, 빌때까지 pop 해라. 맨마지막꺼겠네 한번찍어보자.
		while (!isStackEmpty()){
			dst += ((char)pop());
			System.out.println("남은 연산자를 ~~ pop하는 요소 : "+ dst.charAt(dst.length()-1));
			dst += ' ';
		}
		return dst;
	}

	int cal_postfix(String src){

		int idx = 0;
		while( src.length() -1 >= idx ){

			// 숫자라면 그 수 전체 push(두 자리) 
			// 두 자리 넣는 거 비효율 적인거 같은데, 한글짜씩 49 20 이러면... 그렇지 안되는구나. 4 9 2 0 팝팝팝팝하면 구분이 안돼
			// 바꿔야된다. ' '를 기준으로 
			if( src.charAt(idx) >= '0' && src.charAt(idx) <= '9' ){

				// 다음께 ' '인지 판단하자. 다음께 공백이면 한자리 숫자라는말이니깐 넣어버려
				if( src.charAt(idx +1) == ' ' ){
					push((src.charAt(idx)-48));
					idx += 2;
					// 다음껀 아마 공백이겠지. 공백은 알아서 처리하는 루틴 만들자.
					// 아님 공백 없게 한칸 더 idx++를 시킬까.. 그래보자
				}else if( src.charAt(idx+1) >= '0' && src.charAt(idx+1) <= '9'){
					int temp = (src.charAt(idx)-48)*10 + (src.charAt(idx)-48);
					push(temp); //두자리숫자넣는건데.. ㅇㅇ 상관없다.
					idx += 3;
				}
				// 연산자일때 팝팝~
			} else if ( isOperator(src.charAt(idx)) ){
				int val2 = pop();
				int val1 = pop();
				
//				System.out.println("scr.charAt : " +src.charAt(idx));
//				System.out.println("val1 : "+val1 + " val2 : "+val2);
				int result = 123; 

				// val1 +-*/ val2 한 값 push..
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



