#ifndef TOWERVM_ASSERTS_H
#define TOWERVM_ASSERTS_H

#define ASSERT_INT_EQ(EXP, VAL, NAME)                                          \
  if (!(EXP == VAL)) {                                                         \
    printf("%s... failed (%d != %d)", NAME, EXP, VAL);                         \
    exit(1);                                                                   \
  }

#endif // TOWERVM_ASSERTS_H
