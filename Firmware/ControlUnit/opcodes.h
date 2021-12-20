PROGMEM const byte OP_NOP[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 }
};

// LOAD/STORE A

PROGMEM const byte OP_LDA_i[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | PC_EN, A_I }
};

PROGMEM const byte OP_LDA_a[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | MAR_I | PC_EN, 0 },
    { ALWAYS, MDR_O, A_I }
};

PROGMEM const byte OP_STA_a[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | MAR_I | PC_EN, 0 },
    { ALWAYS, MDR_I, A_O }
};

// JUMP/BRANCH

PROGMEM const byte OP_JMP_a[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | PC_I, 0 }
};

PROGMEM const byte OP_BEQ_az[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, PC_EN, 0 },
    { IF_ZER, MDR_O | PC_I, 0 }
};

PROGMEM const byte OP_BCS_ac[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, PC_EN, 0 },
    { IF_CAR, MDR_O | PC_I, 0 }
};

// I/O

PROGMEM const byte OP_IN_A[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, 0, A_I | IN_O }
};

PROGMEM const byte OP_OUT_A[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, 0, A_O | OUT_I }
};

// ARITHMETIC

PROGMEM const byte OP_ADD_i[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | PC_EN, B_I },
    { ALWAYS, ALU_O, A_I }
};

PROGMEM const byte OP_ADD_a[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | MAR_I | PC_EN, 0 },
    { ALWAYS, MDR_O, B_I },
    { ALWAYS, ALU_O, A_I }
};

PROGMEM const byte OP_SUB_i[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | PC_EN, B_I },
    { ALWAYS, ALU_O, A_I }
};

PROGMEM const byte OP_SUB_a[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | MAR_I | PC_EN, 0 },
    { ALWAYS, MDR_O, B_I },
    { ALWAYS, ALU_O, A_I }
};

PROGMEM const byte OP_CMP_i[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | PC_EN, B_I },
    { ALWAYS, ALU_O }
};

PROGMEM const byte OP_CMP_a[][3] = {
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | CIR_I | PC_EN, 0 },
    { ALWAYS, PC_O | MAR_I, 0 },
    { ALWAYS, MDR_O | MAR_I | PC_EN, 0 },
    { ALWAYS, MDR_O, B_I },
    { ALWAYS, ALU_O }
};
