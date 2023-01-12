


enum class object_t {
    Map_Feature;
    Ship;
    Other;
}

class game_object {
private:
    // geographical data
    double position_x;          // Arbitrary units.
    double position_y;
    double speed_x;
    double speed_y;
    double acceleration_x;
    double acceleration_y;
    double angle;               // In degrees, how the ship is oriented: front towards that direction
    double angle_derivative;    // In degrees per second
    double angle_acceleration;

    object_t object_type;

protected:
    // BASIC FUNCTIONS
    double get_position_x() {
        return this->position_x; }
    double get_position_y() {
        return this->position_y; }
    double get_speed_x() {
        return this->speed_x; }
    double get_speed_y() {
        return this->speed_y; }
    double get_acceleration_x() {
        return this->acceleration_x; }
    double get_acceleration_y() {
        return this->acceleration_y; }
    double get_angle() {
        return this->angle; }
    double get_angle_derivative() {
        return this->angle_derivative; }
    double get_angle_acceleration() {
        return this->angle_acceleration; }

    void set_position_x(double new_x) {
        this->position_x = new_x; }
    void set_position_y(double new_y) {
        this->position_y = new_y; }
    void set_speed_x(double new_x) {
        this->speed_x = new_x; }
    void set_speed_y(double new_y) {
        this->speed_y = new_y; }
    void set_acceleration_x(double new_x) {
        this->acceleration_x = new_x; }
    void set_acceleration_y(double new_y) {
        this->acceleration_y = new_y; }
    void set_angle(double new_angle) {
        this->angle = new_angle; }
    void set_angle_derivative(double new_angle_speed) {
        this->angle_derivative = new_angle_speed; }
    void set_angle_acceleration(double new_angle_acceleration) {
        this->angle_acceleration = new_angle_acceleration; }

// Constructors and destructors
    explicit game_object(double position_x, double position_y, 
                double speed_x, double speed_y, 
                double acceleration_x, double acceleration_y, 
                double angle, double angle_derivative, double angle_acceleration,
                object_t object_type) {
        
        this->position_x = position_x; this->position_y = position_y; 
        this->speed_x = speed_x; this->speed_y = speed_y; 
        this->acceleration_x = acceleration_x; this->acceleration_y = acceleration_y
        this->angle = angle; this->angle_derivative = angle_derivative; this->angle_acceleration = angle_acceleration;
        this->object_type = object_type;
        //this->acceleration_x = 0; this->acceleration_y = 0; this->angle_derivative = 0;
    }
    game_object(game_object other) { // HE WHO COPIES NOTHING CREATES NOTHING
        this->position_x = other->position_x; this->position_y = other->position_y;
        this->speed_x = other->speed_x; this->speed_y = other->speed_y; 
        this->acceleration_x = other->acceleration_x; this->acceleration_y = other->acceleration_y
        this->angle = other->angle; this->angle_derivative = other->angle_derivative; this->angle_acceleration = other->angle_acceleration;
        this->object_type = other->object_type;
    }

    game_object(double position_x, double position_y, 
            double speed_x, double speed_y,
            double angle, double angle_derivative,
            object_t object_type) { // default objects are floating in the void with no acceleration.
        game_object(position_x, position_y, speed_x, speed_y, 0, 0, angle, angle_derivative, 0, object_type);
        }
    
    game_object() = delete; 


    ~game_object();




}