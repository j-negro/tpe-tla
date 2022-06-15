public enum NoteRythm {
    WHOLE(1, 'w'),
    HALF(0.5, 'h'),
    QUARTER(0.25, 'q'),
    EIGHT(0.125, 'i'),
    SIXTEENTH(0.0625, 's'),
    THIRTY_SECOND(0.03125, 't'),
    SIXTY_FOURTH(0.015625, 'x');
    private final double duration;
    private final char symbol;

    NoteRythm(double duration, char symbol) {
        this.duration = duration;
        this.symbol = symbol;
    }

    public double getDuration() {
        return duration;
    }
    public char getSymbol() {
        return symbol;
    }
}
