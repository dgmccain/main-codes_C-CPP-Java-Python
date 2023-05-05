public class BodyMassIndex {
    double BMIHeight;
    double BMIWeight;
    double BMIScore;
    String BMICategory;

    public BodyMassIndex(double height, double weight) {
        BMIHeight = height;
        BMIWeight = weight;
        BMIScore = getBMIScore(BMIHeight, BMIWeight);
        BMICategory = getBMICategory(BMIScore);
    }

    //calculate bmi score from user input obtained in App class...
    public double getBMIScore(double height, double weight) {
        //rounding
        height = Math.round(height * 10); //round height to 1 decimal place - part 1...
        height = height / 10;             //round height to 1 decimal place - part 2...
        weight = Math.round(weight * 10); //round weight same as height...
        weight = weight / 10;
        double bmi = (703 * weight) / (height * height); //703 * pounds for bmi calculation...
        bmi = Math.round(bmi * 10); //round bmi too...
        bmi = bmi / 10;

        return bmi;
    }

    //bmi uses data from height and weight to determine condition...
    public String getBMICategory(double bmi) {
        String result;
        if (bmi < 18.5) {
            result = "Underweight";
        }
        else if (bmi >= 18.5 && bmi <= 24.9) {
            result = "Normal weight";
        }
        else if (bmi >= 25 && bmi <= 29.9) {
            result = "Overweight";
        }
        else {
            result = "Obese";
        }
        return result;
    }
}
