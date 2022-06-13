public class Note implements Comparable<Note> {

    private NoteTone tone;
    private NoteDuration duration;
    private NoteType type;
    private int octave;

    public Note() {
        // A4 Half es valor por defecto por si no se aclaran atributos.
        this.tone = NoteTone.A;
        this.duration = NoteDuration.HALF;
        this.type = NoteType.NORMAL;
        this.octave = 4;
    }

    public NoteTone getTone() {
        return tone;
    }

    public NoteType getType() {
        return type;
    }

    public NoteDuration getDuration() {
        return duration;
    }

    public int getOctave() {
        return octave;
    }

    public Note setTone(NoteTone tone) {
        this.tone = tone;
        return this;
    }

    public Note setType(NoteType type) {
        this.type = type;
        return this;
    }

    public Note setDuration(NoteDuration duration) {
        this.duration = duration;
        return this;
    }

    public Note setOctave(int octave) {
        if (octave < 1)
            this.octave = 1;
        else this.octave = Math.min(octave, 7); // Habíamos definido A1-G7 como los máximos
        return this;
    }

    public Note addInteger(int value) {
        // TODO: La habíamos hecho en el informe pero no aparece en UC. Por las dudas la hago
        NoteTone newTone = NoteTone.values()[(this.tone.ordinal() + value) % NoteTone.values().length];
        int newOctave = this.octave + (value / NoteTone.values().length);
        return new Note().setDuration(this.duration).setTone(newTone).setOctave(newOctave).setType(this.type);
    }

    public Note raiseOctave() {
        return this.setOctave(this.octave + 1);
    }

    public Note lowerOctave() {
        return this.setOctave(this.octave - 1);
    }

    @Override
    public int compareTo(Note o) {
        int result = this.octave - o.octave;
        if (result == 0)
            result = this.tone.ordinal() - o.tone.ordinal();
        return result;
    }
}
