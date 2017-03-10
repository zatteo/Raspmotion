import com.leapmotion.leap.Controller;
import com.leapmotion.leap.HandList;
import com.leapmotion.leap.*;

public class SampleListener extends Listener {
	public Hand handLeft;
	public Hand handRight;

	public void onConnect(Controller controller) {
	    System.out.println("Connected");
	}

	public void onMovtPitch(float mov) {
		if ( mov > 0.3 ) {
			System.out.println("Vers le haut.");
		} else
		if ( mov < -0.3) {
			System.out.println("Vers le bas.");
		} else
		if ( mov >= -0.3 && mov <= 0.3) {
			System.out.println("tout droit.");
		}
	}

	public void onMovtRoll(float mov) {
		if ( mov > 0.35 ) {
			System.out.println("Vers la gauche.");
		} else
		if ( mov < -0.35) {
			System.out.println("Vers la droite.");
		} else
		if ( mov >= -0.35 && mov <= 0.35) {
			System.out.println("tout droit.");
		}
	}


	public void onMovtPalm(float mov) {
		if (mov > 50.) {
			System.out.println("On freine.");
		} else
		if (mov < -50.) {
			System.out.println("Acc�l�ration.");
		} else
		if (mov <= 50. && mov >= -50.) {
			System.out.println("Rien.");
		}
	}

	public void onFist(float angle) {
		if (angle > 3)
			System.out.println("fist");
		else
			System.out.println("not fist");
	}

	public void onFrame(Controller controller) {
        com.leapmotion.leap.Frame frame = controller.frame();

        HandList hands = frame.hands();
        if (hands.isEmpty()) {
        }
        else {
        	if ((hands.get(0)).isRight() ) {
        		handRight = hands.get(0);
        		handLeft = hands.get(1);
        	}
        	else {
        		handRight = hands.get(1);
        		handLeft = hands.get(0);
        	}
	    }

        float pitch = handLeft.direction().pitch();
        float roll = handLeft.palmNormal().roll();

        //roll = gauche/droite
        //	vers 1 ->gauche
        //	vers -1 -> droite

        //pitch = haut/bas
        //	Si augmente, monte
        //	Si diminue, descend

        /**
         * Vector position :
         *     x: gauche-droite
         *     y: haut-bas
         *     z: avant/arri�re -> n�gatif = avant, positif = arri�re
         */
        //System.out.println("pitch main gauche : " + roll);
        onMovtPalm(handLeft.palmPosition().getZ());
        onMovtPitch(pitch);
        onMovtRoll(roll);
        //onFist(handRight.grabAngle());
	}
}
