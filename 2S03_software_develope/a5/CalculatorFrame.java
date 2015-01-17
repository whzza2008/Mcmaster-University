/*
 * Filename: Calculator.java
 * Author: 2S03MakeYouLearnGood
 * Description: This file will teach you about how GUIs are created in Java.
 */

/*
 * Java provides us with 3 default layouts that
 * can be used to well, layout our interfaces.
 * They come from the java.awt package that
 * contains all of the classes for creating
 * user interfaces and for painting graphics and images.
 */
import java.awt.GridLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;



/*
 * We're going to be using the Swing package.
 * It provides a set of "lightweight" (all-Java language) components that
 * (as best as possible) work the same on all platforms.
 *
 * The general hierarchy is: text fields, labels, buttons etc. are ADDED to panels
 * and panels are ADDED to frames.
 *
 * We are going to use panels, frames, text fields and button so we import them.
 */
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JButton;


/* We're making this class CalculatorFrame extend
 * JFrame, which means it in and of itself IS A JFrame.
 */
class CalculatorFrame extends JFrame {

	private static final int NUMBER_PAD_WIDTH = 4;
	private static final int NUMBER_PAD_HEIGHT = 5;
	
	private static final int CALCULATOR_WIDTH = 1;
	private static final int CALCULATOR_HEIGHT = 2;
	
	/* In the end this is what we're looking for
	 *    -------------------
	 *    |               0 |
	 *    -------------------
	 *    | ( | ) | % | AC  |
	 *    -------------------
	 *    | 7 | 8 | 9 |  /  |
	 *    -------------------
	 *    | 4 | 5 | 6 |  *  |
	 *    -------------------
	 *    | 1 | 2 | 3 |  -  |
	 *    -------------------
	 *    | 0 | . | = |  +  |
	 *    -------------------
	 */

	private static final long serialVersionUID = 1L;

	/* We could use many different categories, but we going to use
	 * 3 JPanels, a resultPanel for showing our results, a numberPanel
	 * for holding our buttons and operations and a mainPanel
	 * which will serve as a container for both.
	 */
	private JPanel mainPanel, resultPanel, numberPanel;
	
	private static Set<String> operators = new HashSet<String>();
	private static Set<String> digits = new HashSet<String>();
	
	// Static blocks work like a constructor, but are outside out constructor
	// and typically only used for variable initialization. Lets create a set
	// for our symbols and operators!
	static {
		
		for(String x : new String[]{"(", ")", "+", "-", "*", "/", "%", "=", ".", "AC"})
			operators.add(x);
		
		for(int i = 0; i < 10; i++)
			digits.add(Integer.toString(i));
	}
	
	// The indicates whether the next digit-press should clear the screen or not.
	private boolean clearResultField = true;
	
	// The first number entered and stored into our calculator.
	private Integer firstNumber = null;
	
	// The action/operation entered and stored into our calculator.
	private String action = null;
	
	/* We could have made use of other things such as JLabel, JRadioButton, and JCheckBox etc */

	/* and finally we need a JTextField to hold our results */
	private JTextField resultField;

	public CalculatorFrame() {

		/* Set the title of the window. */
		super("Really Simple Calculator");

		/* result panel */
		resultPanel = new JPanel();

		/* FlowLayout positions components row wise from left to right */
		resultPanel.setLayout(new FlowLayout());
		
		/* We want it to initially say 0 and have a width of about 20 columns */
		resultField = new JTextField("0", 20);
		
		/* Add the text field to its panel */
		resultPanel.add(resultField);
		
		/* Set the alignment */
		resultField.setHorizontalAlignment(JTextField.RIGHT);
		
		/* We don't want it to be editable we just want to display results */
		resultField.setEditable(false);

		/* number panel*/
		numberPanel = new JPanel();
		
		numberPanel.setLayout(new GridLayout(NUMBER_PAD_HEIGHT, NUMBER_PAD_WIDTH));
		
		Map<String, JButton> buttons = new HashMap<String, JButton>();
		
		// Lets build the buttons for digits.
		for(String x : digits)
			buttons.put(x, new JButton(x));
		
		// Lets build the buttons for operators.
		for(String x : operators)
			buttons.put(x, new JButton(x));
		
		// The numbers will appear organized as we have them here. This does not have
		// to be a 2-dimensional array, but it helps visualize things better.
		String[][] buttonOrder = new String[][]{

				{ "(", ")", "%", "AC" },
				{ "7", "8", "9", "/" },
				{ "4", "5", "6", "*" },
				{ "1", "2", "3", "-" },
				{ "0", ".", "=", "+" }
		};
		
		// Lets add our rows to the number panel!
		for(int i = 0; i < NUMBER_PAD_HEIGHT; i++)
			for(int j = 0; j < NUMBER_PAD_WIDTH; j++)
				numberPanel.add(buttons.get(buttonOrder[i][j]));
		
		// Create and add a digit listener to each digit button. Check the implementation
		// of buildDigitListener() below!
		
		ActionListener digitListener = buildDigitListener();
		
		for(String x : digits)
			buttons.get(x).addActionListener(digitListener);
		
		// Create and add an operator listener to each operator button. Check the implementation
		// of buildOperatorListener() below!
		
		ActionListener operatorListener = buildOperatorListener();
		
		for(String x : operators)
			buttons.get(x).addActionListener(operatorListener);
		
		/* we then create our mainPanel which we're going to add everything else to */
		mainPanel = new JPanel();

		/* we make it have 2 rows and 1 column so we can stack our panels */
		mainPanel.setLayout(new GridLayout(CALCULATOR_HEIGHT, CALCULATOR_WIDTH));

		/* and we add both in the order we want them to be displayed */
		mainPanel.add(resultPanel);
		mainPanel.add(numberPanel);

		/* We add our mainPanel to the JFrame */
		add(mainPanel);

		/* Specify that the window should close when the exit button provided by the OS is clicked. */
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		/* We then call pack() which causes the window to be sized
		 * to fit the preferred size and layouts of its subcomponents
		 */
		pack();

		/* and finally set it's visibility to true */
		setVisible(true);
	}
	
	/**
	 * Creates an action listener for digits. This should only be called once!
	 * 
	 * @return An action listener for digits.
	 */
	private ActionListener buildDigitListener(){
		
		return new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				
				/*
				 * We know only JButtons will trigger this event, so it is safe to type case
				 * the 'source' of the event to a JButton type.
				 */
				JButton j = (JButton) e.getSource();
				
				// If the result field should be cleared, do so while adding this digit. Lets also
				// prevent leading zeroes.
				if(clearResultField || resultField.getText().equals("0")){
					
					// We probably should not be relying on the text in the digit as our 'identifier'
					// for that button, but it is sufficient for our purposes for now.
					resultField.setText(j.getText());
					clearResultField = false;
				}
				else {

					resultField.setText(resultField.getText() + j.getText());
				}
			}
		};
	}
	
	/**
	 * Creates an action listener for operators. This should only be called once!
	 * 
	 * @return An action listener for operators.
	 */
	private ActionListener buildOperatorListener(){
		
		return new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				
				/*
				 * We are only going to support +, -, *, / and % operations.
				 * (, ) and . are beyond the needs of our basic calculator.
				 */
				
				// Upon entering an operation, the next digits a user enters should clear the result field.
				clearResultField = true;
				
				JButton j = (JButton) e.getSource();
				
				String operator = j.getText();
				
				/*
				 * This is not a very good way for identifying which operator was pressed (relying on the caption
				 * text of the button), but it is good enough for demonstration purposes! We are 'switching' on the
				 * first character of the operator button caption, because that's enough to identify the operation.
				 * 
				 * If this were used under Java 7, we would be able to switch on the String itself.
				 */
				switch(operator.charAt(0)){
				
					case 'A': // The clear operation.
						
						resultField.setText("0");
						action = null;
						firstNumber = null;
						
						break; // If you are missing 'break', the next case will execute too!
					
					case '=':
						
						if(action != null && firstNumber != null){
							
							// Parse the second number from the resultField text, perform the last-entered operation,
							// and store the result back into the firstNumber field, over-writing the first number.
							firstNumber = doOperation(firstNumber, Integer.parseInt(resultField.getText()), action);
							
							// Put the result into the resultField.
							resultField.setText(firstNumber.toString());
							action = null;
						}
						
						break;
					
					// This case 'falls through'. If +, -, %, / or * are entered, they all execute the same case!
					case '+':
					case '-':
					case '%':
					case '/':
					case '*':
						
						// If there was already a pending operation, perform it. This can make calculations
						// easier for the user to do quickly.
						if(action != null && firstNumber != null){
							
							firstNumber = doOperation(firstNumber, Integer.parseInt(resultField.getText()), action);
							resultField.setText(firstNumber.toString());
							action = operator;
						}
						else {
							
							// Otherwise, parse and store the first number and operator.
							firstNumber = Integer.parseInt(resultField.getText());
							action = operator;
							
							break;
						}
						
					default:
							
				}
			}
		};
	}
	
	/**
	 * Performs some operation on two arguments, based on a string representation of
	 * that operation.
	 * 
	 * @param first The first argument to the operation.
	 * @param second The second argument to the operation.
	 * @param operation The operation to perform, represented as a string.
	 * @return The result of the operation.
	 */
	private static int doOperation(int first, int second, String operation){
		
		/*
		 * It would be better for 'operation' to be an enumerated type, but in the interest
		 * of writing something simple that works, rather than something that resembles a compiler,
		 * lets just do this.
		 */
		switch(operation.charAt(0)){
		
			case '+':
				return first + second;
				
			case '-':
				return first - second;
				
			case '*':
				return first * second;
				
			case '/':
				return first / second;
				
			case '%':
				return first % second;
			
			// It would make more sense to put an exception here. This can
			// be an exercise for the reader!
			default:
				return -1;
		}
	}
}