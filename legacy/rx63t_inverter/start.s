# ===============================================================
# R5F56218BNFP �X�^�[�g�A�b�v
# ===============================================================
	.text

# ===============================================================
# �n�[�h�E�F�A�[�E���Z�b�g
# ===============================================================
	.global _power_on_reset
_power_on_reset:
	.global _start
_start:

# �X�^�b�N�̐ݒ�
	.extern _usp_init
	mvtc	#_usp_init, usp
	.extern _isp_init
	mvtc	#_isp_init, isp

# ���荞�݃x�N�^�̐ݒ�
	.extern _interrupt_vectors
	mov.l	#_interrupt_vectors, r5
	mvtc	r5,intb

	mov.l	#0x100, r5
	mvtc	r5,fpsw

# I���W�X�^��ݒ肵�A���荞�݂�������
	mov.l	#0x00010000, r5
	mvtc	r5,psw

# PM���W�X�^��ݒ肵�A���[�U���[�h�Ɉڍs����
	mvfc	psw,r1
	or		#0x100000, r1
	push.l	r1

# U���W�X�^���Z�b�g���邽�߂�RTE���߂����s����
	mvfc	pc,r1
	add		#0x0a,r1
	push.l	r1
	rte
	nop
	nop

# init() �֐�����J�n
	.extern	_init
	bsr		_init

	.global	_set_intr_level
_set_intr_level:
	and		#15,r1
	shll	#24,r1
	or		#0x100000,r1
	mvtc	r1,psw
	rts
	nop

	.global _exit
_exit:
	wait
	bra		_exit


