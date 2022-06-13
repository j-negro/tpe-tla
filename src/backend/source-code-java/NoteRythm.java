public enum NoteRythm {
    WHOLE(1),
    HALF(0.5),
    QUARTER(0.25),
    EIGHT(0.125),
    SIXTEENTH(0.0625),
    THIRTY_SECOND(0.03125),
    SIXTY_FOURTH(0.015625);
    private final double duration;

    NoteRythm(double duration) {
        this.duration = duration;
    }

    public double getDuration() {
        return duration;
    }
}
