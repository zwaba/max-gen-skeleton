#include "gen_exported.h"

namespace gen_exported {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Data m_BOUL_18;
	Data m_BILL_24;
	Delay m_delay_17;
	Sah __m_sah_40;
	Sah __m_sah_39;
	int __exception;
	int vectorsize;
	t_sample __m_carry_37;
	t_sample __m_count_35;
	t_sample __m_carry_27;
	t_sample __m_count_25;
	t_sample __m_latch_32;
	t_sample m_trigger_23;
	t_sample __m_count_41;
	t_sample __m_count_45;
	t_sample __m_carry_69;
	t_sample __m_latch_76;
	t_sample __m_latch_77;
	t_sample __m_carry_43;
	t_sample __m_count_67;
	t_sample __m_carry_51;
	t_sample __m_latch_65;
	t_sample __m_carry_47;
	t_sample __m_count_49;
	t_sample m_dry_wet_22;
	t_sample m_filter_21;
	t_sample m_speed_20;
	t_sample m_history_4;
	t_sample m_history_5;
	t_sample m_history_6;
	t_sample m_history_7;
	t_sample m_history_3;
	t_sample m_history_1;
	t_sample m_history_2;
	t_sample samplerate;
	t_sample __m_latch_80;
	t_sample m_history_8;
	t_sample m_history_10;
	t_sample m_history_15;
	t_sample m_history_16;
	t_sample m_loop_19;
	t_sample m_history_9;
	t_sample m_history_14;
	t_sample m_history_12;
	t_sample m_history_13;
	t_sample m_history_11;
	t_sample __m_latch_81;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_delay_17.reset("m_delay_17", ((int)5));
		m_BOUL_18.reset("BOUL", ((int)15336000), ((int)2));
		m_loop_19 = 0;
		m_speed_20 = 1;
		m_filter_21 = 0;
		m_dry_wet_22 = 0.5;
		m_trigger_23 = 0;
		m_BILL_24.reset("BILL", ((int)15336000), ((int)2));
		__m_count_25 = 0;
		__m_carry_27 = 0;
		__m_latch_32 = 0;
		__m_count_35 = 0;
		__m_carry_37 = 0;
		__m_sah_39.reset(0);
		__m_sah_40.reset(0);
		__m_count_41 = 0;
		__m_carry_43 = 0;
		__m_count_45 = 0;
		__m_carry_47 = 0;
		__m_count_49 = 0;
		__m_carry_51 = 0;
		__m_latch_65 = 0;
		__m_count_67 = 0;
		__m_carry_69 = 0;
		__m_latch_76 = 0;
		__m_latch_77 = 0;
		__m_latch_80 = 0;
		__m_latch_81 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int BILL_dim = m_BILL_24.dim;
		int BILL_channels = m_BILL_24.channels;
		int dim_623 = BILL_dim;
		int BOUL_dim = m_BOUL_18.dim;
		int BOUL_channels = m_BOUL_18.channels;
		int dim_674 = BOUL_dim;
		bool chan_ignore_29 = ((((int)2) < 0) || (((int)2) >= BOUL_channels));
		t_sample sub_693 = (m_dry_wet_22 - ((t_sample)0.5));
		t_sample scale_690 = ((safepow((sub_693 * ((t_sample)2)), ((int)1)) * ((int)-1)) + ((int)1));
		t_sample min_408 = ((((int)1) < scale_690) ? ((int)1) : scale_690);
		t_sample sub_697 = (m_dry_wet_22 - ((int)0));
		t_sample scale_694 = ((safepow((sub_697 * ((t_sample)2)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample min_412 = ((((int)1) < scale_694) ? ((int)1) : scale_694);
		t_sample round_590 = round(m_trigger_23);
		t_sample resetcountloop_601 = round_590;
		t_sample resetcountloop_604 = resetcountloop_601;
		t_sample round_591 = round(m_loop_19);
		t_sample startstoploop_632 = round_591;
		t_sample startstoploop_611 = startstoploop_632;
		int gte_399 = (m_speed_20 >= ((t_sample)1.9));
		int mul_398 = (gte_399 * ((int)3));
		int lt_397 = (m_speed_20 < ((t_sample)1.9));
		int mul_400 = (lt_397 * ((int)2));
		int lte_396 = (m_speed_20 <= ((t_sample)0.6));
		int mul_395 = (lte_396 * ((int)1));
		int gt_394 = (m_speed_20 > ((t_sample)0.6));
		int mul_393 = (gt_394 * ((int)2));
		__m_latch_32 = (((((gt_394 + lte_396) + lt_397) + gte_399) != 0) ? (((mul_400 + mul_393) + mul_395) + mul_398) : __m_latch_32);
		int latch_405 = __m_latch_32;
		int sub_392 = (latch_405 - ((int)2));
		int choice_33 = sub_392;
		t_sample selector_404 = ((choice_33 >= 3) ? ((int)2) : ((choice_33 >= 2) ? ((int)1) : ((choice_33 >= 1) ? ((t_sample)0.5) : 0)));
		t_sample gen_406 = selector_404;
		t_sample speed_629 = gen_406;
		t_sample speed_593 = speed_629;
		t_sample choice_34 = int(startstoploop_611);
		t_sample selector_592 = ((choice_34 >= 1) ? speed_593 : 0);
		int dim_644 = BOUL_dim;
		t_sample speed_630 = speed_629;
		int dim_670 = BOUL_dim;
		t_sample speed_631 = speed_629;
		int dim_638 = BOUL_dim;
		t_sample startstoploop_633 = startstoploop_632;
		int dim_657 = BOUL_dim;
		t_sample startstoploop_609 = startstoploop_632;
		t_sample resetcountloop_602 = resetcountloop_601;
		int not_603 = (!startstoploop_609);
		t_sample speed_612 = speed_629;
		t_sample speed_595 = speed_629;
		int irange_699 = (dim_644 - ((int)0));
		int orange_700 = (((int)0) - dim_644);
		int irange_703 = (dim_670 - ((int)0));
		int orange_704 = (((int)0) - dim_670);
		bool chan_ignore_60 = ((1 < 0) || (1 >= BOUL_channels));
		bool chan_ignore_61 = ((((int)2) < 0) || (((int)2) >= BILL_channels));
		t_sample count_reset_70 = (resetcountloop_602 + startstoploop_609);
		bool chan_ignore_75 = ((1 < 0) || (1 >= BILL_channels));
		int lte_435 = (m_filter_21 <= ((int)0));
		int not_434 = (!lte_435);
		__m_latch_76 = ((not_434 != 0) ? m_filter_21 : __m_latch_76);
		t_sample latch_436 = __m_latch_76;
		t_sample sub_714 = (latch_436 - ((int)0));
		t_sample scale_711 = ((safepow((sub_714 * ((t_sample)0.01)), ((int)1)) * ((int)995)) + ((int)5));
		t_sample scale_440 = scale_711;
		int gte_438 = (m_filter_21 >= ((int)0));
		int not_437 = (!gte_438);
		__m_latch_77 = ((not_437 != 0) ? m_filter_21 : __m_latch_77);
		t_sample latch_439 = __m_latch_77;
		t_sample sub_718 = (latch_439 - (-100));
		t_sample scale_715 = ((safepow((sub_718 * ((t_sample)0.01)), ((int)1)) * ((int)22500)) + ((int)500));
		t_sample scale_441 = scale_715;
		t_sample min_478 = ((scale_441 < ((int)0)) ? ((int)0) : scale_441);
		t_sample omega = safediv((min_478 * ((t_sample)6.2831853071796)), samplerate);
		t_sample sn = sin(omega);
		t_sample cs = cos(omega);
		t_sample alpha = ((sn * ((t_sample)0.5)) * ((int)2));
		t_sample b0 = safediv(((int)1), (((int)1) + alpha));
		t_sample a2 = (((((int)1) - cs) * ((t_sample)0.5)) * b0);
		t_sample a1 = ((((int)1) - cs) * b0);
		t_sample b1 = ((((int)-2) * cs) * b0);
		t_sample b2 = ((((int)1) - alpha) * b0);
		t_sample expr_494 = a2;
		t_sample expr_495 = a1;
		t_sample expr_496 = a2;
		t_sample expr_497 = b1;
		t_sample expr_498 = b2;
		t_sample min_450 = ((scale_440 < ((int)0)) ? ((int)0) : scale_440);
		t_sample omega_503 = safediv((min_450 * ((t_sample)6.2831853071796)), samplerate);
		t_sample sn_506 = sin(omega_503);
		t_sample cs_508 = cos(omega_503);
		t_sample alpha_507 = ((sn_506 * ((t_sample)0.5)) * ((t_sample)2));
		t_sample b_500 = safediv(((int)1), (((int)1) + alpha_507));
		t_sample a_501 = (((((int)1) + cs_508) * ((t_sample)0.5)) * b_500);
		t_sample a_505 = ((-(((int)1) + cs_508)) * b_500);
		t_sample b_504 = ((((int)-2) * cs_508) * b_500);
		t_sample b_502 = ((((int)1) - alpha_507) * b_500);
		t_sample expr_466 = a_501;
		t_sample expr_467 = a_505;
		t_sample expr_468 = a_501;
		t_sample expr_469 = b_504;
		t_sample expr_470 = b_502;
		int lte_511 = (m_filter_21 <= ((int)0));
		int not_510 = (!lte_511);
		__m_latch_80 = ((not_510 != 0) ? m_filter_21 : __m_latch_80);
		t_sample latch_512 = __m_latch_80;
		t_sample sub_723 = (latch_512 - ((int)0));
		t_sample scale_720 = ((safepow((sub_723 * ((t_sample)0.01)), ((int)1)) * ((int)995)) + ((int)5));
		t_sample scale_516 = scale_720;
		int gte_514 = (m_filter_21 >= ((int)0));
		int not_513 = (!gte_514);
		__m_latch_81 = ((not_513 != 0) ? m_filter_21 : __m_latch_81);
		t_sample latch_515 = __m_latch_81;
		t_sample sub_727 = (latch_515 - (-100));
		t_sample scale_724 = ((safepow((sub_727 * ((t_sample)0.01)), ((int)1)) * ((int)22500)) + ((int)500));
		t_sample scale_517 = scale_724;
		t_sample min_554 = ((scale_517 < ((int)0)) ? ((int)0) : scale_517);
		t_sample omega_683 = safediv((min_554 * ((t_sample)6.2831853071796)), samplerate);
		t_sample sn_688 = sin(omega_683);
		t_sample cs_685 = cos(omega_683);
		t_sample alpha_681 = ((sn_688 * ((t_sample)0.5)) * ((int)2));
		t_sample b_684 = safediv(((int)1), (((int)1) + alpha_681));
		t_sample a_680 = (((((int)1) - cs_685) * ((t_sample)0.5)) * b_684);
		t_sample a_687 = ((((int)1) - cs_685) * b_684);
		t_sample b_686 = ((((int)-2) * cs_685) * b_684);
		t_sample b_682 = ((((int)1) - alpha_681) * b_684);
		t_sample expr_570 = a_680;
		t_sample expr_571 = a_687;
		t_sample expr_572 = a_680;
		t_sample expr_573 = b_686;
		t_sample expr_574 = b_682;
		t_sample min_526 = ((scale_516 < ((int)0)) ? ((int)0) : scale_516);
		t_sample omega_579 = safediv((min_526 * ((t_sample)6.2831853071796)), samplerate);
		t_sample sn_581 = sin(omega_579);
		t_sample cs_578 = cos(omega_579);
		t_sample alpha_582 = ((sn_581 * ((t_sample)0.5)) * ((t_sample)2));
		t_sample b_583 = safediv(((int)1), (((int)1) + alpha_582));
		t_sample a_576 = (((((int)1) + cs_578) * ((t_sample)0.5)) * b_583);
		t_sample a_580 = ((-(((int)1) + cs_578)) * b_583);
		t_sample b_584 = ((((int)-2) * cs_578) * b_583);
		t_sample b_577 = ((((int)1) - alpha_582) * b_583);
		t_sample expr_542 = a_576;
		t_sample expr_543 = a_580;
		t_sample expr_544 = a_576;
		t_sample expr_545 = b_584;
		t_sample expr_546 = b_577;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			__m_count_25 = (((int)0) ? 0 : (fixdenorm(__m_count_25 + ((int)1))));
			int carry_26 = 0;
			if ((((int)0) != 0)) {
				__m_count_25 = 0;
				__m_carry_27 = 0;
				
			} else if (((dim_674 > 0) && (__m_count_25 >= dim_674))) {
				int wraps_28 = (__m_count_25 / dim_674);
				__m_carry_27 = (__m_carry_27 + wraps_28);
				__m_count_25 = (__m_count_25 - (wraps_28 * dim_674));
				carry_26 = 1;
				
			};
			int counter_675 = __m_count_25;
			int counter_676 = carry_26;
			int counter_677 = __m_carry_27;
			bool index_ignore_30 = ((counter_675 >= BOUL_dim) || (counter_675 < 0));
			if ((!(chan_ignore_29 || index_ignore_30))) {
				m_BOUL_18.write(in2, counter_675, ((int)2));
				
			};
			bool index_ignore_31 = ((counter_675 >= BOUL_dim) || (counter_675 < 0));
			if ((!index_ignore_31)) {
				m_BOUL_18.write(in1, counter_675, 0);
				
			};
			t_sample mul_586 = (in2 * min_408);
			t_sample mul_587 = (in1 * min_408);
			__m_count_35 = (resetcountloop_604 ? 0 : (fixdenorm(__m_count_35 + selector_592)));
			int carry_36 = 0;
			if ((resetcountloop_604 != 0)) {
				__m_count_35 = 0;
				__m_carry_37 = 0;
				
			} else if (((dim_623 > 0) && (__m_count_35 >= dim_623))) {
				int wraps_38 = (__m_count_35 / dim_623);
				__m_carry_37 = (__m_carry_37 + wraps_38);
				__m_count_35 = (__m_count_35 - (wraps_38 * dim_623));
				carry_36 = 1;
				
			};
			t_sample counter_624 = __m_count_35;
			int counter_625 = carry_36;
			int counter_626 = __m_carry_37;
			int count_671 = counter_675;
			int sah_662 = __m_sah_39(count_671, (round_590 + round_591), ((int)0));
			int sah_646 = sah_662;
			int sah_645 = sah_646;
			t_sample sah_610 = __m_sah_40(counter_624, not_603, ((int)0));
			t_sample sahloop_414 = sah_610;
			t_sample sahloop_407 = sahloop_414;
			t_sample mul_391 = (sahloop_407 * ((t_sample)0.00125));
			t_sample mul_390 = (mul_391 * (-1));
			t_sample tap_589 = m_delay_17.read_step(((int)8));
			t_sample trig_649 = tap_589;
			t_sample trig_647 = trig_649;
			int eq_648 = ((startstoploop_633 + trig_647) == ((int)0));
			__m_count_41 = (eq_648 ? 0 : (fixdenorm(__m_count_41 + speed_630)));
			int carry_42 = 0;
			if ((eq_648 != 0)) {
				__m_count_41 = 0;
				__m_carry_43 = 0;
				
			} else if (((sah_646 > 0) && (__m_count_41 >= sah_646))) {
				int wraps_44 = (__m_count_41 / sah_646);
				__m_carry_43 = (__m_carry_43 + wraps_44);
				__m_count_41 = (__m_count_41 - (wraps_44 * sah_646));
				carry_42 = 1;
				
			};
			t_sample counter_651 = __m_count_41;
			int counter_652 = carry_42;
			int counter_653 = __m_carry_43;
			int endcountpart_636 = counter_653;
			int add_650 = (endcountpart_636 + ((int)1));
			int endcountpart_635 = endcountpart_636;
			int eq_637 = (endcountpart_635 == ((int)0));
			__m_count_45 = (eq_637 ? 0 : (fixdenorm(__m_count_45 + speed_631)));
			int carry_46 = 0;
			if ((eq_637 != 0)) {
				__m_count_45 = 0;
				__m_carry_47 = 0;
				
			} else if (((dim_638 > 0) && (__m_count_45 >= dim_638))) {
				int wraps_48 = (__m_count_45 / dim_638);
				__m_carry_47 = (__m_carry_47 + wraps_48);
				__m_count_45 = (__m_count_45 - (wraps_48 * dim_638));
				carry_46 = 1;
				
			};
			t_sample counter_639 = __m_count_45;
			int counter_640 = carry_46;
			int counter_641 = __m_carry_47;
			t_sample sub_701 = (counter_639 - ((int)0));
			t_sample scale_698 = ((safepow(safediv(sub_701, irange_699), ((int)1)) * orange_700) + dim_644);
			t_sample scale_643 = scale_698;
			t_sample countpart_634 = scale_643;
			int eq_656 = ((startstoploop_632 + trig_649) == ((int)0));
			__m_count_49 = (eq_656 ? 0 : (fixdenorm(__m_count_49 + speed_629)));
			int carry_50 = 0;
			if ((eq_656 != 0)) {
				__m_count_49 = 0;
				__m_carry_51 = 0;
				
			} else if (((dim_657 > 0) && (__m_count_49 >= dim_657))) {
				int wraps_52 = (__m_count_49 / dim_657);
				__m_carry_51 = (__m_carry_51 + wraps_52);
				__m_count_49 = (__m_count_49 - (wraps_52 * dim_657));
				carry_50 = 1;
				
			};
			t_sample counter_658 = __m_count_49;
			int counter_659 = carry_50;
			int counter_660 = __m_carry_51;
			t_sample sub_705 = (counter_658 - ((int)0));
			t_sample scale_702 = ((safepow(safediv(sub_705, irange_703), ((int)1)) * orange_704) + dim_670);
			t_sample scale_669 = scale_702;
			t_sample sub_654 = (scale_669 - ((int)15336000));
			t_sample add_655 = (sub_654 + sah_645);
			int choice_53 = add_650;
			t_sample selector_661 = ((choice_53 >= 2) ? countpart_634 : ((choice_53 >= 1) ? add_655 : 0));
			int index_trunc_54 = fixnan(floor(selector_661));
			bool index_ignore_55 = ((index_trunc_54 >= BOUL_dim) || (index_trunc_54 < 0));
			// samples BOUL channel 1;
			t_sample sample_BOUL_678 = (index_ignore_55 ? 0 : m_BOUL_18.read(index_trunc_54, 0));
			t_sample index_BOUL_679 = selector_661;
			t_sample recloop_622 = sample_BOUL_678;
			int index_trunc_56 = fixnan(floor(counter_624));
			bool index_ignore_57 = ((index_trunc_56 >= BILL_dim) || (index_trunc_56 < 0));
			if ((!index_ignore_57)) {
				m_BILL_24.write(recloop_622, index_trunc_56, 0);
				
			};
			t_sample recloop_388 = recloop_622;
			t_sample mul_386 = (recloop_388 * ((t_sample)0.8));
			int index_trunc_58 = fixnan(floor(selector_661));
			bool index_ignore_59 = ((index_trunc_58 >= BOUL_dim) || (index_trunc_58 < 0));
			// samples BOUL channel 1;
			// samples BOUL channel 2;
			t_sample sample_BOUL_663 = (index_ignore_59 ? 0 : m_BOUL_18.read(index_trunc_58, 0));
			t_sample sample_BOUL_664 = ((chan_ignore_60 || index_ignore_59) ? 0 : m_BOUL_18.read(index_trunc_58, 1));
			t_sample index_BOUL_665 = selector_661;
			t_sample recloop_621 = sample_BOUL_663;
			int index_trunc_62 = fixnan(floor(counter_624));
			bool index_ignore_63 = ((index_trunc_62 >= BILL_dim) || (index_trunc_62 < 0));
			if ((!(chan_ignore_61 || index_ignore_63))) {
				m_BILL_24.write(recloop_621, index_trunc_62, ((int)2));
				
			};
			t_sample recloop_389 = recloop_621;
			t_sample mul_387 = (recloop_389 * ((t_sample)0.8));
			int bool_597 = (counter_624 != 0);
			int openreset_596 = bool_597;
			int choice_64 = openreset_596;
			t_sample selector_594 = ((choice_64 >= 1) ? speed_595 : 0);
			int openreset_598 = openreset_596;
			__m_latch_65 = ((openreset_598 != 0) ? resetcountloop_601 : __m_latch_65);
			t_sample latch_600 = __m_latch_65;
			int not_599 = (!latch_600);
			int choice_66 = not_599;
			t_sample selector_606 = ((choice_66 >= 2) ? speed_612 : ((choice_66 >= 1) ? ((int)0) : 0));
			__m_count_67 = ((resetcountloop_602 + startstoploop_609) ? 0 : (fixdenorm(__m_count_67 + (selector_594 + selector_606))));
			int carry_68 = 0;
			if ((count_reset_70 != 0)) {
				__m_count_67 = 0;
				__m_carry_69 = 0;
				
			} else if (((sahloop_407 > 0) && (__m_count_67 >= sahloop_407))) {
				int wraps_71 = (__m_count_67 / sahloop_407);
				__m_carry_69 = (__m_carry_69 + wraps_71);
				__m_count_67 = (__m_count_67 - (wraps_71 * sahloop_407));
				carry_68 = 1;
				
			};
			t_sample counter_613 = __m_count_67;
			int counter_614 = carry_68;
			int counter_615 = __m_carry_69;
			t_sample sub_427 = (counter_613 - mul_390);
			t_sample irange_707 = (sahloop_414 - ((int)0));
			t_sample sub_709 = (sub_427 - ((int)0));
			t_sample scale_706 = ((safepow(safediv(sub_709, irange_707), ((int)1)) * ((int)1)) + ((int)0));
			t_sample scale_418 = scale_706;
			t_sample mod_422 = safemod(scale_418, ((int)1));
			t_sample window = ((int)0);
			t_sample pointer = mod_422;
			if ((((int)0) == ((int)0))) {
				t_sample v_72 = (mod_422 * ((int)500));
				pointer = ((v_72 <= ((int)0)) ? ((int)0) : ((v_72 >= ((int)1)) ? ((int)1) : v_72));
				t_sample scaled = (pointer * ((t_sample)6.2831853071796));
				window = ((((int)1) - cos(scaled)) * ((t_sample)0.5));
				
			};
			t_sample expr_424 = window;
			t_sample mul_420 = (expr_424 * (-1));
			t_sample add_419 = (mul_420 + ((int)1));
			t_sample gen_425 = add_419;
			int index_trunc_73 = fixnan(floor(counter_613));
			bool index_ignore_74 = ((index_trunc_73 >= BILL_dim) || (index_trunc_73 < 0));
			// samples BILL channel 1;
			// samples BILL channel 2;
			t_sample sample_BILL_616 = (index_ignore_74 ? 0 : m_BILL_24.read(index_trunc_73, 0));
			t_sample sample_BILL_617 = ((chan_ignore_75 || index_ignore_74) ? 0 : m_BILL_24.read(index_trunc_73, 1));
			t_sample index_BILL_618 = counter_613;
			t_sample loop_607 = sample_BILL_616;
			t_sample mul_429 = (gen_425 * loop_607);
			t_sample mix_710 = (mul_429 + (((t_sample)0.5) * (mul_387 - mul_429)));
			t_sample mix_433 = mix_710;
			t_sample mul_488 = (mix_433 * expr_494);
			t_sample mul_485 = (m_history_14 * expr_495);
			t_sample mul_483 = (m_history_16 * expr_496);
			t_sample mul_479 = (m_history_15 * expr_498);
			t_sample mul_481 = (m_history_13 * expr_497);
			t_sample sub_487 = (((mul_483 + mul_485) + mul_488) - (mul_481 + mul_479));
			t_sample gen_493 = sub_487;
			t_sample history_484_next_489 = fixdenorm(m_history_14);
			t_sample history_480_next_490 = fixdenorm(m_history_13);
			t_sample history_486_next_491 = fixdenorm(mix_433);
			t_sample history_482_next_492 = fixdenorm(sub_487);
			t_sample gen_499 = gen_493;
			t_sample mul_460 = (gen_499 * expr_466);
			t_sample mul_457 = (m_history_10 * expr_467);
			t_sample mul_455 = (m_history_11 * expr_468);
			t_sample mul_451 = (m_history_12 * expr_470);
			t_sample mul_453 = (m_history_9 * expr_469);
			t_sample sub_459 = (((mul_455 + mul_457) + mul_460) - (mul_453 + mul_451));
			t_sample gen_465 = sub_459;
			t_sample history_452_next_461 = fixdenorm(m_history_9);
			t_sample history_456_next_462 = fixdenorm(m_history_10);
			t_sample history_458_next_463 = fixdenorm(gen_499);
			t_sample history_454_next_464 = fixdenorm(sub_459);
			t_sample mul_410 = (gen_465 * min_412);
			t_sample add_431 = (mul_586 + mul_410);
			t_sample out2 = add_431;
			int index_trunc_78 = fixnan(floor(counter_613));
			bool index_ignore_79 = ((index_trunc_78 >= BILL_dim) || (index_trunc_78 < 0));
			// samples BILL channel 1;
			t_sample sample_BILL_619 = (index_ignore_79 ? 0 : m_BILL_24.read(index_trunc_78, 0));
			t_sample index_BILL_620 = counter_613;
			t_sample loop_608 = sample_BILL_619;
			t_sample mul_428 = (gen_425 * loop_608);
			t_sample mix_719 = (mul_428 + (((t_sample)0.5) * (mul_386 - mul_428)));
			t_sample mix_432 = mix_719;
			t_sample mul_564 = (mix_432 * expr_570);
			t_sample mul_561 = (m_history_6 * expr_571);
			t_sample mul_559 = (m_history_7 * expr_572);
			t_sample mul_555 = (m_history_8 * expr_574);
			t_sample mul_557 = (m_history_5 * expr_573);
			t_sample sub_563 = (((mul_559 + mul_561) + mul_564) - (mul_557 + mul_555));
			t_sample gen_569 = sub_563;
			t_sample history_556_next_565 = fixdenorm(m_history_5);
			t_sample history_560_next_566 = fixdenorm(m_history_6);
			t_sample history_562_next_567 = fixdenorm(mix_432);
			t_sample history_558_next_568 = fixdenorm(sub_563);
			t_sample gen_575 = gen_569;
			t_sample mul_536 = (gen_575 * expr_542);
			t_sample mul_533 = (m_history_2 * expr_543);
			t_sample mul_531 = (m_history_4 * expr_544);
			t_sample mul_527 = (m_history_3 * expr_546);
			t_sample mul_529 = (m_history_1 * expr_545);
			t_sample sub_535 = (((mul_531 + mul_533) + mul_536) - (mul_529 + mul_527));
			t_sample gen_541 = sub_535;
			t_sample history_532_next_537 = fixdenorm(m_history_2);
			t_sample history_528_next_538 = fixdenorm(m_history_1);
			t_sample history_534_next_539 = fixdenorm(gen_575);
			t_sample history_530_next_540 = fixdenorm(sub_535);
			t_sample mul_411 = (gen_541 * min_412);
			t_sample add_430 = (mul_587 + mul_411);
			t_sample out1 = add_430;
			m_delay_17.write(round_590);
			m_history_16 = history_484_next_489;
			m_history_9 = history_454_next_464;
			m_history_10 = history_458_next_463;
			m_history_11 = history_456_next_462;
			m_history_12 = history_452_next_461;
			m_history_13 = history_482_next_492;
			m_history_14 = history_486_next_491;
			m_history_15 = history_480_next_490;
			m_history_8 = history_556_next_565;
			m_history_1 = history_530_next_540;
			m_history_2 = history_534_next_539;
			m_history_3 = history_528_next_538;
			m_history_4 = history_532_next_537;
			m_history_5 = history_558_next_568;
			m_history_6 = history_562_next_567;
			m_history_7 = history_560_next_566;
			m_delay_17.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_BOUL(void * _value) {
		m_BOUL_18.setbuffer(_value);
	};
	inline void set_loop(t_param _value) {
		m_loop_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_speed(t_param _value) {
		m_speed_20 = (_value < 0.5 ? 0.5 : (_value > 2 ? 2 : _value));
	};
	inline void set_filter(t_param _value) {
		m_filter_21 = (_value < -100 ? -100 : (_value > 100 ? 100 : _value));
	};
	inline void set_dry_wet(t_param _value) {
		m_dry_wet_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_trigger(t_param _value) {
		m_trigger_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_BILL(void * _value) {
		m_BILL_24.setbuffer(_value);
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 7; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_BILL(ref); break;
		case 1: self->set_BOUL(ref); break;
		case 2: self->set_dry_wet(value); break;
		case 3: self->set_filter(value); break;
		case 4: self->set_loop(value); break;
		case 5: self->set_speed(value); break;
		case 6: self->set_trigger(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		
		
		case 2: *value = self->m_dry_wet_22; break;
		case 3: *value = self->m_filter_21; break;
		case 4: *value = self->m_loop_19; break;
		case 5: *value = self->m_speed_20; break;
		case 6: *value = self->m_trigger_23; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(7 * sizeof(ParamInfo));
	self->__commonstate.numparams = 7;
	// initialize parameter 0 ("m_BILL_24")
	pi = self->__commonstate.params + 0;
	pi->name = "BILL";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_BOUL_18")
	pi = self->__commonstate.params + 1;
	pi->name = "BOUL";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_dry_wet_22")
	pi = self->__commonstate.params + 2;
	pi->name = "dry_wet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_dry_wet_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_filter_21")
	pi = self->__commonstate.params + 3;
	pi->name = "filter";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_filter_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -100;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_loop_19")
	pi = self->__commonstate.params + 4;
	pi->name = "loop";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_loop_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_speed_20")
	pi = self->__commonstate.params + 5;
	pi->name = "speed";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_speed_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 2;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_trigger_23")
	pi = self->__commonstate.params + 6;
	pi->name = "trigger";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_trigger_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // gen_exported::
