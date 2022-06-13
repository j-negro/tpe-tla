public class Note implements Comparable<Note> {

    private NoteTone tone;
    private NoteRythm rythm;
    private NoteType type;
    private int octave;

    public Note() {
        // A4 Half es valor por defecto por si no se aclaran atributos.
        this.tone = NoteTone.A;
        this.rythm = NoteRythm.HALF;
        this.type = NoteType.NORMAL;
        this.octave = 4;
    }

    public NoteTone getTone() {
        return tone;
    }

    public NoteType getType() {
        return type;
    }

    public NoteRythm getRythm() {
        return rythm;
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

    public Note setRythm(NoteRythm rythm) {
        this.rythm = rythm;
        return this;
    }

    public Note setOctave(int octave) {
        // TODO: En informe pusimos 1-7, pero en Flex tomamos 2-6.
        if (octave < 2)
            this.octave = 2;
        else this.octave = Math.min(octave, 6);
        return this;
    }

    public Note addInteger(int value) {
        // TODO: La habíamos hecho en el informe pero no aparece en UC. Por las dudas la hago
        NoteTone newTone = NoteTone.values()[(this.tone.ordinal() + value) % NoteTone.values().length];
        int newOctave = this.octave + (value / NoteTone.values().length);
        return new Note().setRythm(this.rythm).setTone(newTone).setOctave(newOctave).setType(this.type);
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

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(this.tone.name());
        if (this.type == NoteType.FLAT)
            sb.append("b");
        else if (this.type == NoteType.SHARP)
            sb.append("#");
        sb.append(this.octave);
        return sb.toString();
    }
}
