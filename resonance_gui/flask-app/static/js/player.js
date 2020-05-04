import Tone from '../node_modules/tone';
import io from '../node_modules/socket.io-client/dist/socket.io';


const AudioContext = window.AudioContext || window.webkitAudioContext;

// VARIABLES, SETTINGS
const sound = {
	context : null,
	masterGain : null,
	tracks : [],
	signals: {}
}

const sampleFilePath = 'static/playerSamples/';
const eventsFilePath = 'static/playerEvents/';


/*
// PRESETS

defaultPreset will determine what loads when you first open Resonance.
const defaultPreset = {
	signals: [ 
		{
			channel: '/channel_name',   	// starts with a slash to tell them apart from ranges.
			ranges: [						// A range is a smaller segment of the full range of the signal
				{							
					name: 'range_name',
					min: (lowest value),
					max: (highest value)
				},
				{
					name: 'range_name2',	// "relative: true" sets the min and max to the lowest and
					relative: true 			// highest of the channel so far, these will change over time 
				}, 							
				{
					name: 'range_name3',	// Using "relative: true" along with min and max sets the
					relative: true,			// limits to min and max as long as the signal is between them,
					min: (some value),		// then expands the limits once the signals exceeds these
					max: (some value)
				}
			]
		},
		{
			channel: '/channel_name2',
			ranges: [
				...
			]
		}
	],	
	tracks: [								// Each track corresponds to a single soundfile
		{	
			fileName: 'harp_main.ogg',		// soundfiles need to be in the folder specified as sampleFilePath above
			gain: -2,
			loopLength: 5,					// loopLength: how long of a segment of the track plays on each loop, in seconds
			decayCutoff: 0.1,				// decayCutoff: calculated value under which the track is silent 
			inputs: [						// inputs determine how the track responds to signals
				{ 	
					range:'spr_alpha_theta_fullrange',		
					type:'loopPoint',		// check readme.md for instructions on how to set up inputs
					value:'avg5',
					min: 0.2,
					peak: 0.45,
					max: 0.45,
					decayBoost: 0.3,
					decayRate: 0.4,
					decayRange: 0.15
				},
				{ 	range:'spr_alpha_theta_fullrange',
					type:'volume',
					value:'avg3',
					min: 0.2,
					peak: 0.4,
					max: 0.6,
					decayRate: 0.4,
					decayRange: 0.15
				}
				]
		},
}


*/

const defaultPreset = {
	signals: [ {
			channel: '/fp_dpli_left_midline',
			ranges: [
				{
					name: 'fp_dpli_left_midline_lead',
					min: 0.51,
					max: 0.7
				},
				{
					name: 'fp_dpli_left_midline_mid',
					min: 0.49,
					max: 0.51
				},
				{
					name: 'fp_dpli_left_midline_lag',
					min: 0.30,
					max: 0.49
				}
			]
		},
		{ 	channel: '/fp_dpli_left_lateral',
			ranges: [
				{
					name: 'fp_dpli_left_lateral_lead',
					min: 0.51,
					max: 0.7
				},
				{
					name: 'fp_dpli_left_lateral_mid',
					min: 0.49,
					max: 0.51
				},
				{
					name: 'fp_dpli_left_lateral_lag',
					min: 0.30,
					max: 0.49
				}
			]
		},
		{ 	channel: '/fp_dpli_right_midline',
			ranges: [
				{
					name: 'fp_dpli_right_midline_lead',
					min: 0.51,
					max: 0.7
				},
				{
					name: 'fp_dpli_right_midline_mid',
					min: 0.49,
					max: 0.51
				},
				{
					name: 'fp_dpli_right_midline_lag',
					min: 0.30,
					max: 0.49
				}
			]
		},
		{ 	channel: '/fp_dpli_right_lateral',
			ranges: [
				{
					name: 'fp_dpli_right_lateral_lead',
					min: 0.51,
					max: 0.7
				},
				{
					name: 'fp_dpli_right_lateral_mid',
					min: 0.49,
					max: 0.51
				},
				{
					name: 'fp_dpli_right_lateral_lag',
					min: 0.30,
					max: 0.49
				}
			]
		},
		{ 	channel: '/fp_wpli_left_midline',
			ranges: [
				{
					name: 'fp_wpli_left_midline',
					min: 0.03,
					max: 0.4
				}
			]
		},
		{ 	channel: '/fp_wpli_left_lateral',
			ranges: [
				{
					name: 'fp_wpli_left_lateral',
					min: 0.03,
					max: 0.4
				}
			]
		},
		{ 	channel: '/fp_wpli_right_midline',
			ranges: [
				{
					name: 'fp_wpli_right_midline',
					min: 0.03,
					max: 0.4
				}
			]
		},
		{ 	channel: '/fp_wpli_right_lateral',
			ranges: [
				{
					name: 'fp_wpli_right_lateral',
					min: 0.03,
					max: 0.4
				}
			]
		},
		{ 	channel: '/hl_relative_position',
			ranges: [
				{
					name: 'hl_front',
					min: 0.,
					max: 0.6
				},
				{
					name: 'hl_back',
					min: 0.5,
					max: 1
				}
			]
		},
		{ 	channel: '/pe_frontal',
			ranges: [
				{
					name: 'pe_frontal_rel',
					relative: true,				
				},
				{	name: 'pe_frontal_abs',
					min: 0.4,
					max: 1
				},
				{	name: 'pe_frontal_diff',
					min: -1,
					max: 1
				}
			]
		},
		{ 	channel: '/pe_parietal',
			ranges: [
				{
					name: 'pe_parietal_rel',
					relative: true,
				},
				{	name: 'pe_parietal_abs',
					min: 0.4,
					max: 1
				}
			]
		},
		{
			channel: '/pe_combined', // custom signal combining frontal and parietal
			ranges: [
				{
					name: 'pe_combined', // frontal minus parietal
					min: 0.,
					max: 0.07
				},
				{
					name: 'pe_combined_rel',
					relative: true
				}
			]
		},
		{ 	channel: '/pac_rpt_frontal',
			ranges: []
		},
		{ 	channel: '/pac_rpt_parietal',
			ranges: [
				{
					name: 'pac_rpt_parietal',
					min: 0.8,
					max: 1.2
				}

			]
		},
		{ 	channel: '/spr_beta_alpha',
			ranges: [
				{
					name: 'spr_beta_alpha_gloc',
					min: -2,
					max: -1,
				},
				{
					name: 'spr_beta_alpha_full',
					min: -1.5,
					max: 1.5,
				},
				{
					name: 'spr_beta_alpha_high',
					min: 0,
					max: 2
				}
			]
		},
		{ 	channel: '/spr_alpha_theta',
			ranges: [
				{
					name: 'spr_alpha_theta_fullrange',
					min: -1.5,
					max: 1.5
				},
				{
					name: 'spr_alpha_theta_relative',
					min: -0.6,
					max: -0.4,
					relative: true,
					value: 'avg3'
				},

			]
		},
		{ 	channel: '/td_front_back',
			ranges: [
				{
					name: 'td_front_back',
					min: 0.9,
					max: 1.1,
				}
			]
		}
	],
	tracks: [
	{	fileName: 'SPRa-t_harp_main.ogg',
		gain: -6,
		loopLength: 5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'spr_alpha_theta_fullrange',
					type:'loopPoint',
					value:'avg5',
					min: 0.2,
					peak: 0.45,
					max: 0.45,
					decayBoost: 0.4,
					decayRate: 0.7,
					decayRange: 0.1
				},
				{ 	range:'spr_alpha_theta_fullrange',
					type:'volume',
					value:'avg3',
					min: 0.2,
					peak: 0.4,
					max: 0.6,
					decayRate: 0.6,
					decayRange: 0.1
				}
				]
	},
	{	fileName: 'SPRa-t_harp_melody.ogg',
		gain: -6,
		loopLength: 5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'spr_alpha_theta_fullrange',
					type:'loopPoint',
					value:'avg5',
					min: 0.2,
					peak: 0.45,
					max: 0.45,
					decayBoost: 0.5,
					decayRate: 0.7,
					decayRange: 0.1
				},
				{ 	range:'spr_alpha_theta_fullrange',
					type:'volume',
					value:'diff5',
					min: 0.5,
					peak: 0.75,
					max: 0.75,
					decayRate: 0.8,
					decayRange: 0.1
				}
				]
	},
	{	fileName: 'SPRa-t_pianoascending.ogg',
		gain: -5,
		loopLength: 5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'spr_alpha_theta_fullrange',
					type:'loopPoint',
					value:'avg5',
					min: 0.4,
					peak: 0.8,
					max: 0.8,
					decayBosst: 0.25,
					decayRate: 0.5,
					decayRange: 0.05 },
				{ 	range:'spr_alpha_theta_fullrange',
					type:'volume',
					value:'avg3',
					min: 0.4,
					peak: 0.6,
					max: 0.8,
					decayBosst: 0.25,
					decayRate: 0.4,
					decayRange: 0.05 }
				]
	},
	{	fileName: 'PAC_rhodes.ogg',
		gain: -12,
		loopLength: 5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'pac_rpt_parietal',
					type:'loopPoint',
					value:'avg5',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.7,
					decayBoost: 0.3,
					decayRange: 0.1 }
				]
	},
	{ 	fileName: 'SPRb-a_softersynth.ogg',
		gain: -5,
		loopLength: 4,
		decayCutoff: 0.2,
		inputs: [{	range:'spr_beta_alpha_full',
					type:'loopPoint',
					value: 'avg3',
					min: 0.2,
					peak: 0.8,
					max: 0.8,
					decayBoost: 0.6,
					decayRate: 0.6,
					decayRange: 0.05 },
				{	range:'spr_beta_alpha_full',
					type:'volume',
					value: 'avg3',
					min: 0.2,
					peak: 0.5,
					max: 0.8,
					decayBoost: 0.6,
					decayRate: 0.6,
					decayRange: 0.05 }
				]
	},

	{	fileName: 'SPRb-a_slow_gloc_melody.ogg',
		gain: -10,
		inputs: [{	range: 'spr_beta_alpha_full',
					type: 'volume',
					value: 'curr',
					min: 0,
					peak: 0.1,
					max: 0.2,
					decayRate: 0.7,
					decayRange: 0.2
		}]
	},
	{
		fileName: 'HL_flutedrone.ogg',
		gain: -12,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_front',
					type: 'volume',
					value: 'avg5',
					min: 0,
					peak: .3,
					max: 0.7,
					decayRate: 0.6,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'HL_thindrone.ogg',
		gain: -8,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_front',
					type: 'volume',
					value: 'avg5',
					min: 0.5,
					peak: 0.8,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.4,
					decayBoost: 0.2,
				}
			]
	},
	{
		fileName: 'HL-cello.ogg',
		gain: -15,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_back',
					type: 'volume',
					value: 'avg5',
					min: 0,
					peak: 0.5,
					max: 1,
					decayRate: 0.7,
					decayRange: 0.15,
					decayBoost: 0.3
				}
			]
	},
		{
		fileName: 'HL-viola.ogg',
		gain: -15,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_back',
					type: 'volume',
					value: 'avg5',
					min: 0.25,
					peak: 0.66,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.15,
					decayBoost: 0.3
				}
			]
	},	{
		fileName: 'HL-violin2.ogg',
		gain: -15,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_back',
					type: 'volume',
					value: 'avg5',
					min: 0.33,
					peak: 0.75,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.15,
					decayBoost: 0.3
				}
			]
	},	{
		fileName: 'HL-violin1.ogg',
		gain: -15,
		decayCutoff: 0.2,
		inputs: [{	range: 'hl_back',
					type: 'volume',
					value: 'avg5',
					min: 0.5,
					peak: 0.8,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.3
				}
			]
	},
	{
		fileName: 'PE-drum.ogg',
		gain: -5,
		decayCutoff: 0.05,
		inputs: [{	range: 'pe_combined',
					type: 'volume',
					value: 'avg5',
					min: 0.1,
					peak: 0.5,
					max: 0.5,
					decayRate: 0.6,
					decayRange: 0.1,
					decayBoost: 0.6
		},
		{			range: 'pe_combined',
					type: 'playbackRate',
					value: 'avg5',
					playbackMin: 0.6,
					playbackSpeedup: 2,
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1,
					decayBoost: 0.5
		}
		]
	},
	{
		fileName: 'PE-kick.ogg',
		gain: -5,
		decayCutoff: 0.05,
		inputs: [{	range: 'pe_combined',
					type: 'volume',
					value: 'avg5',
					min: 0,
					peak: 0.4,
					max: 0.4,
					decayRate: 0.7,
					decayRange: 0.1,
					decayBoost: 0.5
		},
		{			range: 'pe_combined',
					type: 'playbackRate',
					value: 'avg5',
					playbackMin: 0.6,
					playbackSpeedup: 2,
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.7,
					decayRange: 0.1,
					decayBoost: 0.5
		}
		]
	},
	{
		fileName: 'PE-hi-hat.ogg',
		gain: -5,
		decayCutoff: 0.05,
		inputs: [{	range: 'pe_combined',
					type: 'volume',
					value: 'avg5',
					min: 0.5,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1,
					decayBoost: 0.5
		},
		{			range: 'pe_combined',
					type: 'playbackRate',
					value: 'avg5',
					playbackMin: 0.6,
					playbackSpeedup: 2,
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1,
					decayBoost: 0.5
		}]
	},	
	{
		fileName: 'PE-tambourine.ogg',
		gain: -5,
		decayCutoff: 0.05,
		inputs: [{	range: 'pe_combined',
					type: 'volume',
					value: 'avg5',
					min: 0.3,
					peak: 0.6,
					max: 0.6,
					decayRate: 0.5,
					decayRange: 0.1,
					decayBoost: 0.3
			},
		{			range: 'pe_combined',
					type: 'playbackRate',
					value: 'avg5',
					playbackMin: 0.6,
					playbackSpeedup: 2,
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.5
		}
		]
	},	
	{
		fileName: 'PE-cymbal.ogg',
		gain: -5,
		decayCutoff: 0.05,
		inputs: [{	range: 'pe_combined',
					type: 'volume',
					value: 'avg5',
					min: 0.7,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.2,
					decayBoost: 0.3
		},
		{			range: 'pe_combined',
					type: 'playbackRate',
					value: 'avg5',
					playbackMin: 0.6,
					playbackSpeedup: 2,
					min: 0.,
					peak: 1,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.15,
					decayBoost: 0.5
		}]
	},
	{
		fileName: 'PE-noise.ogg',
		gain: -20,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_frontal_abs',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 0.8,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.1,
					decayBoost: 0.5
		}]
	},
	{	fileName: 'PE-noise2.ogg',
		gain: -20,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_parietal_abs',
					type: 'volume',
					value: 'avg3',
					min: 0.0,
					peak: 0.8,
					max: 1,
					decayRate: 0.5,
					decayRange: 0.1,
					decayBoost: 0.5
		}]
	},
	{	fileName: 'PE_expanseloop.ogg',
		gain: -20,
		decayCutoff: 0.1,
		inputs: [{	range: 'pe_frontal_abs',
					type: 'volume',
					value: 'avg3',
					min: 0.0,
					peak: 1,
					max: 1,
					decayRate: 0.7,
					decayRange: 0.1,
					decayBoost: 0.2
		}]
	},
	{	fileName: 'PE_microtwinkle.ogg',
		gain: -10,
		loopLength: 4,
		decayCutoff: 0.15,
		inputs: [{	range:'pe_frontal_abs',
					type: 'volume',
					value: 'curr',
					min: 0.85,
					peak: 1,
					max: 1,
					decayBoost: 0.3,
					decayRate: 0.4,
					decayRange: 0.25
				},
				{	range:'pe_frontal_abs',
					type: 'loopPoint',
					value: 'avg3',
					min: 0,
					peak: 0.75,
					max: 1,
					decayBoost: 0.4,
					decayRate: 0.4,
					decayRange: 0.25

				}
			]
	},
	{	fileName: 'TD-synthwithfilters.ogg',
		gain: -18,
		loopLength: 0.75,
		decayCutoff: 0.15,
		inputs: [
				{	range:'td_front_back',
					type: 'loopPoint',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayBoost: 0.3,
					decayRate: 0.6,
					decayRange: 0.25

				}
			]
	},


	// values of dPLI that are less than 0.5 - these are the ones that indicate consciousness
	{	fileName: 'dpliLLconscious.ogg',
		gain: -2,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_left_lateral_lag',
					type:'loopPoint',
					value: 'curr',
					min: 0.5,
					peak: 0.5,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_left_lateral_lag',
					type:'volume',
					value: 'curr',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_lateral',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliLMconscious.ogg',
		gain: -2,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_left_midline_lag',
					type:'loopPoint',
					value: 'curr',
					min: 0.5,
					peak: 0.5,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_left_midline_lag',
					type:'volume',
					value: 'curr',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_midline',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliRMconscious.ogg',
		gain: -2,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_right_midline_lag',
					type:'loopPoint',
					value: 'curr',
					min: 0.5,
					peak: 0.5,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_right_midline_lag',
					type:'volume',
					value: 'curr',
					min: 0.8,
					peak: 0.8,
					max: 1,

					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_midline',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliRLconscious.ogg',
		gain: -2,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_right_lateral_lag',
					type:'loopPoint',
					value: 'curr',
					min: 0.5,
					peak: 0.5,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_right_lateral_lag',
					type:'volume',
					value: 'curr',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_lateral',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},

	//  phase-lead values of dPLI
	{	fileName: 'dpliLL_lead.ogg',
		gain: -5,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_left_lateral_lead',
					type:'loopPoint',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_left_lateral_lead',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 0.2,
					max: 0.2,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_lateral',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliLM_lead.ogg',
		gain: -5,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs:[{ 	range:'fp_dpli_left_midline_lead',
					type:'loopPoint',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_left_midline_lead',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 0.2,
					max: 0.2,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_left_midline',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliRM_lead.ogg',
		gain: -5,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_right_midline_lead',
					type:'loopPoint',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_dpli_right_midline_lead',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 0.2,
					max: 0.2,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_midline',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{	fileName: 'dpliRL_lead.ogg',
		gain: -5,
		loopLength: 1.5,
		decayCutoff: 0.1,
		inputs: [{ 	range:'fp_dpli_right_lateral_lead',
					type:'loopPoint',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1 ,
					decayRate: 0.6,
					decayRange: 0.1},
				{ 	range:'fp_dpli_right_lateral_lead',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 0.2,
					max: 0.2,
					decayBoost: 0.5,
					decayRate: 0.6,
					decayRange: 0.1 },
				{ 	range:'fp_wpli_right_lateral',
					type:'volume',
					value: 'curr',
					min: 0,
					peak: 1,
					max: 1,
					decayRate: 0.6,
					decayRange: 0.1 }
				]
	},
	{
		fileName: 'wPLI-LL-flute-high.ogg',
		gain: -2,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_left_lateral',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_left_lateral_lag',
					type: 'volume',
					value: 'avg3',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'wPLI-LL-flute-mid.ogg',
		gain: -10,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_left_lateral',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_left_lateral_mid',
					type: 'volume',
					value: 'avg3',
					min: 0.3,
					peak: 0.5,
					max: 0.7,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'wPLI-LM-bassoon-high.ogg',
		gain: -2,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_left_midline',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_left_midline_lag',
					type: 'volume',
					value: 'avg3',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'wPLI-LM-bassoon-mid.ogg',
		gain: -7,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_left_midline',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_left_midline_mid',
					type: 'volume',
					value: 'avg3',
					min: 0.3,
					peak: 0.5,
					max: 0.7,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'wPLI-RM-horn-high.ogg',
		gain: -2,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_right_midline',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_right_midline_lag',
					type: 'volume',
					value: 'avg3',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'wPLI-RM-horn-mid.ogg',
		gain: -10,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_right_midline',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_right_midline_mid',
					type: 'volume',
					value: 'avg3',
					min: 0.3,
					peak: 0.5,
					max: 0.7,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'wPLI-RL-clarinet-high.ogg',
		gain: -2,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_right_lateral',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_right_lateral_lag',
					type: 'volume',
					value: 'avg3',
					min: 0.8,
					peak: 0.8,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	{
		fileName: 'wPLI-RL-clarinet-mid.ogg',
		gain: -10,
		decayCutoff: 0.2,
		inputs: [{	range: 'fp_wpli_right_lateral',
					type: 'volume',
					value: 'avg3',
					min: 0,
					peak: 1,
					max: 1,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				},
				{	range: 'fp_dpli_right_lateral_mid',
					type: 'volume',
					value: 'avg3',
					min: 0.3,
					peak: 0.5,
					max: 0.7,
					decayThreshold: 0.4,
					decayBoost: 0.1,
					decayRate: 0.4,
					decayRange: 0.2
				}
			]
	},
	]
}


// CLASSES

// Signal are the collection of messags on a range, each also has an associated DOM element
// A channel is the message address - /spr_beta_alpha or /pe_frontal, etc.
class Signal {
	constructor (signal) {
		this.channel = signal.channel;
		this.muted = false;
		this.min = null;
		this.max = null;
		this.prev = null;
		this.mute = false;
		this.curr = 0;
		this.avg3 = 0;
		this.avg5 = 0;
		this.avg10 = 0;
		this.diff3 = 0;
		this.diff5 = 0;
		this.diff10 = 0;
		this.diff3_10 = 0;
		this.last10 = [];
		this.ranges = {}

		// populate the signal with Range objects
		signal.ranges.forEach(range => {
			this.ranges[range.name] = new Range(range);
		});


		// generate the GUI on the right side of the screen
		// most elements have DOM handles so that they can be accessed easily later
		let signalListGUI = document.getElementById('signalContainer'); // the larger box w all signals

		this.signalGUI = document.createElement('div');
		this.signalGUI.innerHTML = `<div>${this.channel}</div>`
		let signalTableGUI = document.createElement('table'); // table with titles and stats
		signalTableGUI.innerHTML = `<tr><td>min</td><td>curr</td><td>max</td><td>avg3</td><td>avg5</td><td>avg10</td></tr>`
		
		this.signalTableRow = document.createElement('tr');  // the row with the actual stats
		this.minGUI = this.createGUI();
		this.currGUI = this.createGUI();
		this.currGUI.classList.add('currentValue');
		this.maxGUI = this.createGUI();
		this.avg3GUI = this.createGUI();
		this.avg5GUI = this.createGUI();
		this.avg10GUI = this.createGUI();

		signalTableGUI.appendChild(this.signalTableRow);

		let signalStats = document.createElement('div'); // contains title, labels and stats
		signalStats.appendChild(this.signalGUI);
		signalStats.appendChild(signalTableGUI);

		let signalButtons = document.createElement('div');
		signalButtons.classList.add('signalButtons');
		this.editButton = document.createElement('button');
		this.editButton.innerText = 'EDIT';
		this.editButton.addEventListener('click', () => {
			this.showEditGUI();
		})
		this.muteButton = document.createElement('button'); // button mutes prevents signals from passing through
		this.muteButton.innerText = 'MUTE';
		this.muteButton.addEventListener('click', () => {
			if (this.muted) {
				this.muteButton.innerText = 'MUTE';
				this.muteButton.classList.remove('muted');
				this.muted = false;
				console.log(this.channel + ' is no longer muted');
			} else {
				this.muteButton.innerText = 'UNMUTE';
				this.muteButton.classList.add('muted');
				this.muted = true;
				console.log(this.channel + " is now muted");
			}
		})
		signalButtons.appendChild(this.editButton);
		signalButtons.appendChild(this.muteButton);

		let signalBox = document.createElement('div'); // the box around this specific signal
		signalBox.classList.add('signalBox'); // for CSS formatting
		signalBox.appendChild(signalStats);
		signalBox.appendChild(signalButtons);

		signalListGUI.appendChild(signalBox);
	}

	createGUI () {
		let gui = document.createElement('td');
		gui.innerText = '';
		this.signalTableRow.appendChild(gui);
		return gui;
	}

	static processMessage(message) {
		// This function is the first step in processing an incoming message. 
		// It does pre-processing and creates any combined signals

		console.log(message);
		let messageIn = JSON.parse(JSON.stringify(message)); // fix problem w aliasing

		// filter out muted signals
		if (sound.signals[messageIn.address].muted) {
			console.log('messageIn muted! ' + messageIn.address);
			return 0;
		}

		// This is taking the log 10 of the spectral power ratios, this makes a nicer signal to sonify
		if (messageIn.address === '/spr_beta_alpha' || messageIn.address === '/spr_alpha_theta') {
			messageIn.args[0] = Math.log10(messageIn.args[0]);
		}


		// This actually updates the signals
		sound.signals[messageIn.address].update(messageIn);

		// post-processing:

		// This is creating a signal that compares the parietal and frontal Permutation Entropy
		// Of two permutation entropy signals, frontal is always sent first, then parietal, so we're
		// looking for parietal in order to make the comparison
		if (messageIn.address === '/pe_parietal') {

			let newValue = sound.signals['/pe_frontal'].curr - sound.signals['/pe_parietal'].curr;

			let newMessage = {
				address: '/pe_combined',
				args: [newValue]
			}

			Signal.processMessage(newMessage);
		}

		// This is setting the threshold of a low-pass filter, depending on the TD.
		if (messageIn.address === '/td_front_back') {
			let newFrequency = Math.pow(sound.signals['/td_front_back'].avg5,5) * 8000
			if (newFrequency > 800) {
				sound.filter.frequency.linearRampToValueAtTime(newFrequency, 10);
			} else {
				sound.filter.frequency.linearRampToValueAtTime(1200, 10);
			}
		}

		// Send the transformed message to each track.
		Track.processMessage(messageIn);
	}

	static getChannel(rangeName) {
		// takes a string rangeName and returns the channel that has that range
		for (const signal in sound.signals) {
			for (const range in sound.signals[signal].ranges ) {
				if (rangeName === range) {
					return signal;
				}
			}
		}

		return 'not found';
	}

	update (message) {
		// update last 10 messages
		if (this.last10.length == 10) { this.last10.shift(); }
		this.last10.push(message.args[0]);

		if (this.max === null || message.args[0] > this.max) {this.max = message.args[0]}
		if (this.min === null || message.args[0] < this.min) {this.min = message.args[0]}

		this.prev = this.curr;
		this.curr = message.args[0];

		this.diff3 = this.curr - this.avg3;
		this.diff5 = this.curr - this.avg5;
		this.diff10 = this.curr - this.avg10;

		this.avg3 = this.last10.slice(-3).reduce((a,c)=>{return a+c})/this.last10.slice(-3).length;
		this.avg5 = this.last10.slice(-5).reduce((a,c)=>{return a+c})/this.last10.slice(-5).length;
		this.avg10 = this.last10.slice(-10).reduce((a,c)=>{return a+c})/this.last10.slice(-10).length;

		this.diff3_10 = this.avg3 - this.avg10;

		// update ranges
		for (const range in this.ranges) {
			this.ranges[range].update();
		}

		this.display();
	}

	display () {
		this.maxGUI.innerText = this.max.toFixed(3);
		this.minGUI.innerText = this.min.toFixed(3);
		this.currGUI.innerText = this.curr.toFixed(3);
		this.avg3GUI.innerText = this.avg3.toFixed(3);
		this.avg5GUI.innerText = this.avg5.toFixed(3);
		this.avg10GUI.innerText = this.avg10.toFixed(3);
	}

	showEditGUI () {
		console.log("showing edit for " + this.channel);
		let editPanel = document.getElementById('resonanceEdit');

		editPanel.innerHTML = `
			<b>${this.channel}</b><br>
		`
	}

	getJSON () {
		let preset = {'channel':this.channel}
		preset.ranges = Object.keys(this.ranges).map((range) => {
			return {'name':this.ranges[range].name, 'min': this.ranges[range].min, 'max': this.ranges[range].max, 'relative': this.ranges[range].relative}
		})
		return preset;
	}

}

// A single track manages playback of a single soundfile.
class Track {
	constructor (track) {

		this.fileName = track.fileName;
		this.muted = false; // muted tracks do update with data, just volume stays 0
		this.inputs = [];
		this.loopLength = track.loopLength ? track.loopLength : 6; // loop duration in seconds - actually the time between successive starts, signal plays for 1 1/2 times the loop length
		this.decayRate = track.decayRate ? track.decayRate : 0.5;
		this.decayCutoff = track.decayCutoff ? track.decayCutoff : 0.1;

		// Add the GUI element to the mixer
		let mixerGUI = document.getElementById('resonanceMixer');
		this.mixerTrack = document.createElement('div');
		this.mixerTrack.classList.add('mixerTrack');
		mixerGUI.appendChild(this.mixerTrack);

		this.loadBuffers();

		// create and connect audio nodes
		this.userGain = sound.context.createGain();
		this.dataGain = sound.context.createGain();
		this.decayGain = sound.context.createGain();
		this.player.connect(this.userGain);
		this.userGain.connect(this.dataGain);
		this.dataGain.connect(this.decayGain);
		this.decayGain.connect(sound.masterGain);

		// create & activate the mixer GUI elements
		// this would all be so simple in React
		this.userGainSlider = Track.createSlider(track.gain);
		this.userGain.gain.value = Math.pow(10, this.userGainSlider.value/20);
		this.userGainSlider.classList.add('userGainSlider');
		this.userGainSlider.addEventListener('input', ()=>{
			this.userGain.gain.setTargetAtTime(Math.pow(10, this.userGainSlider.value/20), sound.context.currentTime, 0.1);
		});

		this.dataGainSlider = Track.createSlider();
		this.dataGainSlider.classList.add('dataGainSlider');
		this.dataGainSlider.setAttribute('disabled', true);
		this.dataGain.gain.setTargetAtTime(0, sound.context.currentTime, 0.1);

		this.decayGainSlider = Track.createSlider();
		this.decayGainSlider.classList.add('decayGainSlider');
		this.decayGainSlider.setAttribute('disabled', true);

		// set up track inputs
		track.inputs.map(input => this.createInput(input));

		// display the GUI
		let infoGUI = document.createElement('div');
		infoGUI.innerText = this.fileName;
		infoGUI.setAttribute('class','mixerTrackInfo');

		this.editButton = document.createElement('button');
		this.editButton.innerText = 'EDIT';
		this.editButton.addEventListener('click', () => {
			this.showEditGUI();
		})
		this.muteButton = document.createElement('button'); // button mutes prevents signals from passing through
		this.muteButton.innerText = 'M';
		this.muteButton.addEventListener('click', () => {
			if (this.muted) {
				this.muteButton.classList.remove('muted');
				this.muted = false;
				console.log(this.fileName + ' is no longer muted');
				// when a track is unmuted it only comes back after the next message
			} else {
				this.muteButton.classList.add('muted');
				this.muted = true;
				this.dataGain.gain.setTargetAtTime(0, sound.context.currentTime, 0.5);
				console.log(this.fileName + " is now muted");
			}
		})

		let buttons = document.createElement('div');
		buttons.appendChild(this.editButton);
		buttons.appendChild(this.muteButton);
		buttons.classList.add('mixerTrackButtons');

		let infoAndButtons = document.createElement('div');
		infoAndButtons.appendChild(infoGUI);
		infoAndButtons.appendChild(buttons);
		this.mixerTrack.appendChild(infoAndButtons);

		let slidersGUI = document.createElement('div');
		slidersGUI.setAttribute('class','mixerTrackSliders');
		slidersGUI.appendChild(this.userGainSlider);
		slidersGUI.appendChild(this.dataGainSlider);
		slidersGUI.appendChild(this.decayGainSlider);
		this.mixerTrack.appendChild(slidersGUI);

		// display info about inputs
		this.inputsGUI = document.createElement('table');
		this.displayInputs();
		this.inputsGUI.setAttribute('class','mixerTrackInputs')
		this.mixerTrack.appendChild(this.inputsGUI);
	}

	static createSlider(gain) { // default gain value
		let slider = document.createElement('input');
		slider.setAttribute('class', 'h-slider');
		slider.setAttribute('type', 'range');
		slider.setAttribute('min', '-20');
		slider.setAttribute('max', '0');
		slider.setAttribute('step', '1');
		slider.setAttribute('value', gain ? gain : -10);
		slider.setAttribute('orient', 'horizonal');
		return slider;
	}

	static processMessage(message) {
		// searches the list of tracks and inputs for matching message channel
		sound.tracks.forEach((track)=>{
			track.update(message);
		})
	}

	loadBuffers () {
		// load the file and create Tone.js player
		let buffer = new Tone.Buffer(sampleFilePath + this.fileName, ()=>{this.length = buffer.duration;})
		let buffer2 = new Tone.Buffer(sampleFilePath + this.fileName, ()=>{})
		this.player = new Tone.Player(buffer);
		this.player.autostart = true;
		this.player.loop = true;
		this.player.fadeIn = this.loopLength / 2.;
		this.player.fadeOut = this.loopLength / 2.;
		// set up for looping
		this.player2 = new Tone.Player(buffer2); // used in loopPoint messages
		this.player2.autostart = false;
		this.player2.loop = false;
		this.player2.fadeIn = this.loopLength / 2.;
		this.player2.fadeOut = this.loopLength / 2.;
		this.looping = false;
		this.nextLoopPlayer = this.player;
		// for now just always 50% overlap, linear fade up and down, listen to it
	}

	deleteTrack () {
		this.player.stop();
		this.player.disconnect();
		this.player2.stop();
		this.player2.disconnect();
		this.mixerTrack.remove();
		for (let i = 0; i<sound.tracks.length; i++) {
			console.log(i);
			if (Object.is(sound.tracks[i], this)) {
				console.log('track ' + i);
				sound.tracks.splice(i, 1);
				break;
			}
		}
	}

	displayInputs () {
		this.inputsGUI.innerHTML = '';
		this.inputs.forEach((input) => {

			let signal = sound.signals[Signal.getChannel(input.range)];
			let range = signal.ranges[input.range];
			let newInput = document.createElement('tr');
			newInput.innerHTML = `
				<td class='input-type'>${input.type}</td>
				<td class='input-data'>${input.value}</td>
				<td class='input-range'>${input.range}</td>
				<td class='input-minpeakmax'>${input.min}</td>
				<td class='input-minpeakmax'>${input.peak}</td>
				<td class='input-minpeakmax'>${input.max}</td><td>of</td>
				<td class='input-data'>${range.min}</td>
				<td class='input-data'>${range.max}</td>
				<td class='input-data'>${signal[input.value].toFixed(3)}</td>
				<td class='input-data'><b>${input.current.toFixed(3)}<b></td>
				<td class='input-data'>${input.decayValue.toFixed(3)}</td>`
			this.inputsGUI.appendChild(newInput);
		})

	}

	createInput(input) {
		this.inputs.push(new Input(input))
	}

	calculateValue(input, range, channel) {
		// got a message and matched it with an input to this track.
		let value = sound.signals[channel][input.value];
		let rangeSpread = range.max - range.min;

		// determine the range of the signal we are looking for
		let inputMin = (input.min * rangeSpread) + range.min ;
		let inputMax = (input.max * rangeSpread) + range.min ;
		let inputPeak = (input.peak * rangeSpread) + range.min;

		let newValue = 0;

		// if range min and max are the same, signal is always on
		if (inputMax == inputMin) {
			newValue = 1;
		}
		// case where the peak equals the max means it stays on above the max
		else if (inputMax == inputPeak) {
			newValue = (value - inputMin)/(inputMax-inputMin);
		}
		// case where the peak equals min, it stays on below min
		else if (inputMin == inputPeak) {
			newValue = 1 - ((value - inputMin)/(inputMax-inputMin));
		}
		// otherwise signal value depends on whether it is above or below peak
		else if (value > inputMin && value < inputPeak) {
			newValue = (value - inputMin)/(inputPeak-inputMin);
		}
		else if (value >= inputPeak && value < inputMax) {
			newValue = 1 - ((value - inputPeak)/(inputMax-inputPeak));
		}

		// clean up out-of-range values
		if (newValue < 0) {newValue = 0}
		if (newValue > 1) {newValue = 1}

		return newValue; // returns a number from 0 to 1 for this input
	}

	update (message) {

		let gainChanged = false; // allows for several volume inputs to same track, they are multiplied
		let changedGain = 0;
		let newGain;
		let ranges = sound.signals[message.address].ranges;

		this.inputs.forEach((input) => {
			for (const rangeName in ranges) {
				let range = ranges[rangeName];
				if (input.range == range.name){

					if (input.type === 'volume' ) { // calculates results of all volume inputs when it sees the first one

						newGain = this.calculateValue(input, range, message.address);
						input.updateDecay(newGain);
					}

					if (input.type == 'loopPoint') {
						// adjust looping behaviour
						// calculate at what point of the file to start
						let value  = this.calculateValue(input, range, message.address)

						input.updateDecay(value);

						let startPoint = value*(this.length-this.loopLength);

						// calculate "momentum" bsed on current signal vs average
						let momentum = (sound.signals[Signal.getChannel(input.range)].curr - sound.signals[Signal.getChannel(input.range)].avg3)*this.length*0.05; // not safe for all channels!
						//let momentum = 0.01*this.length;
						//let momentum = 0

						if (!this.looping) {
							this.player.stop(sound.context.currentTime + (this.loopLength / 2));
							this.player2.start(sound.context.currentTime, startPoint, sound.context.currentTime + 1.5*this.loopLength);
							this.looping = true;
						}
						clearTimeout(this.nextLoop);
						this.triggerNextGrain(startPoint, momentum);
					}

					if (input.type == 'playbackRate') {
						let value = this.calculateValue(input, range, message.address);
						input.updateDecay(value);

						let playbackMin = input.playbackMin;
						let playbackTimes = input.playbackSpeedup;


						let newRate = playbackMin + value*playbackTimes;
						newRate = Number(newRate.toFixed(4));

						this.player.playbackRate = newRate;
						this.player2.playbackRate = newRate;
					}
				}
			}
		})

		// calculate track decay

		let newDecayGain = this.inputs.reduce((sum, input) => {
			return sum + input.decayValue;
		}, 0)/this.inputs.length;


		this.decayGainSlider.value = (newDecayGain * 20) - 20;
		let targetGain = Math.pow(10, this.decayGainSlider.value/20);
		if (newDecayGain < this.decayCutoff) {targetGain = 0;}
		// ramps to new gain in 3 secondsk
		this.decayGain.gain.setTargetAtTime(targetGain, sound.context.currentTime, 3);


		// calculate the track volume

		newGain = this.inputs.reduce((product, input) => {
			if (input.type === 'volume') {
				return product * input.current;
			}
			return product;
		}, 1);

		this.dataGainSlider.value = (newGain * 20) - 20;
		targetGain = Math.pow(10, this.dataGainSlider.value/20);

		// assures that muted tracks and tracks where the new gain is 0 are not audible
		// newGain check has to happen because the previous calculation does not return 0
		if (newGain == 0 || this.muted) {targetGain = 0;}
		// ramps to new gain in 3 seconds
		this.dataGain.gain.setTargetAtTime(targetGain, sound.context.currentTime, 3);

		this.displayInputs();
	}

	checkForLoop() {
		let hasLoop = false
		this.inputs.forEach(input => {
			if (input.type === 'loopPoint') { hasLoop = true }
		})
		return hasLoop
	}

	triggerNextGrain(startPoint, momentum) {

		// catch the cases where momentum takes us outside of bounds
		if (startPoint > (this.length - 1.5*(this.loopLength) - momentum )) { startPoint = this.length - 1.5*(this.loopLength) - momentum - 1};
		if (startPoint < 0)  {startPoint = 0};

		this.nextLoopPlayer.start(sound.context.currentTime, startPoint, sound.context.currentTime + 1.5*this.loopLength);
		this.nextLoopPlayer == this.player ? this.nextLoopPlayer = this.player2 : this.nextLoopPlayer = this.player;

		if (sound.context.state == 'running') {
			this.nextLoop = setTimeout(()=>{this.triggerNextGrain(startPoint + momentum, momentum)}, this.loopLength*1000);
		}
		return true;
	}

	showEditGUI() {
		// creates the edit GUI
		console.log("Show edit GUI for track " + this.fileName);
		let editPanel = document.getElementById('resonanceEdit');

		editPanel.innerHTML = `
			<div class='flex-row'>
				<div><b>${this.fileName}</b><button id='closeTrackEdit'>Close</div>
				<button id='deleteTrackButton'>Delete Track</button>
			</div>
			<div class='flex-row'>
				<input type='file' id='editTrackSoundfile'></input>
				<button id='editTrackSoundfileButton'>Change Soundfile</button>	
			</div>
			<div class='flex-row'>
				<div>loop length (seconds): ${this.checkForLoop() ? "<input id='editLoopLength' class='numberInput' type='number' min='0' step='0.1' value=" + this.loopLength + "></input>" : 'No loopPoint inputs'}</div>
				<div>decay cutoff: <input id='editDecayCutoff' class='numberInput' type='number' min='0' max='1' step='0.01' value='${this.decayCutoff}'></input></div>
			</div>
			<div id='editInputs'></div>
		`

		// event listeners for tracks
		document.getElementById('closeTrackEdit').addEventListener('click', () => {
			editPanel.innerHTML = '';
		})

		document.getElementById('deleteTrackButton').addEventListener('click', () => {
			if (event.target.innerText === 'Delete Track') {
				event.target.innerText = 'Confirm?';
			} else {
				this.deleteTrack();
				editPanel.innerHTML = '';
			}
		})

		document.getElementById('editTrackSoundfileButton').addEventListener('click', () => {
			let newSoundFile = document.getElementById('editTrackSoundfile').value.split('\\');
			if (newSoundFile != '') {
				newSoundFile = newSoundFile[newSoundFile.length - 1];
				this.fileName = newSoundFile;
				this.loadBuffers();
			} else {
				console.log('please select a soundfile');
			}

			let filename = document.getElementById('newTrackFileInput').value.split('\\');
			if (filename != '') {
				filename = filename[filename.length - 1];
				let newTrack = loadTrack({fileName: filename, inputs: []});
				document.getElementById('newTrackFileInput').value = '';
				console.log('added track ' + filename);
				newTrack.showEditGUI();
			} else {
				console.log('please select a sound file before adding a Track');
			}
		})

		let editLoopLength = document.getElementById('editLoopLength')
		if (editLoopLength) {
			editLoopLength.addEventListener('change', () => {
				this.loopLength = event.target.value;
			})
		}

		document.getElementById('editDecayCutoff').addEventListener('change', () => {
			this.decayCutoff = event.target.value;
		})

		// create and populate the list of inputs
		let editInputsPanel = document.getElementById('editInputs');
		for (let input in this.inputs) {
			let editInputItem = document.createElement('div');
			editInputItem.setAttribute('class', 'editInput');

			editInputItem.innerHTML = `
					<b>Input ${input}</b><br>
					<div class='flex-row'>
						<div>Type: 
							<select id='input${input}Type'>
								<option value='volume' ${(this.inputs[input].type === 'volume') ? 'selected' : ''}>volume</option>
								<option value='loopPoint' ${(this.inputs[input].type === 'loopPoint') ? 'selected' : ''}>loopPoint</option>
								<option value='playbackRate' ${(this.inputs[input].type === 'playbackRate') ? 'selected' : ''}>playbackRate<option>
							</select>
						</div>
						<div>Value:
							<select id='input${input}Value'>
								<option value='curr' ${(this.inputs[input].value === 'curr') ? 'selected' : ''}>current</option>
								<option value='avg3' ${(this.inputs[input].value === 'avg3') ? 'selected' : ''}>avg3</option>
								<option value='avg5' ${(this.inputs[input].value === 'avg5') ? 'selected' : ''}>avg5</option>
								<option value='avg10' ${(this.inputs[input].value === 'avg10') ? 'selected' : ''}>avg10</option>
								<option value='diff3' ${(this.inputs[input].value === 'diff3') ? 'selected' : ''}>diff3</option>
								<option value='diff5' ${(this.inputs[input].value === 'diff5') ? 'selected' : ''}>diff5</option>
								<option value='diff10' ${(this.inputs[input].value === 'diff10') ? 'selected' : ''}>diff10</option>
								<option value='diff3_10' ${(this.inputs[input].value === 'diff3_10') ? 'selected' : ''}>diff3_10</option>
							</select>
						</div>
						<div>Range:
							<select id='input${input}Range'>
							</select>
						</div>
						<button id='deleteInput${input}'>Delete</button>
					</div>
					<div class='flex-row'>
						Min: <input id='input${input}Min' class='numberInput' type='number' value='${this.inputs[input].min}' step='0.01'></input>
						Peak: <input id='input${input}Peak' class='numberInput' type='number' value='${this.inputs[input].peak}' step='0.01'></input>
						Max: <input id='input${input}Max' class='numberInput' type='number' value='${this.inputs[input].max}' step='0.01'></input>
						Range Min: <input id='input${input}RangeMin' class='numberInput' type='number' value='${this.inputs[input].getRange().min}' step='0.01'></input>
						Range Max: <input id='input${input}RangeMax' class='numberInput' type='number' value='${this.inputs[input].getRange().max}' step='0.01'></input>
					</div>
					<b>Decay Settings</b>
					<div class='flex=row'>
						Boost: <input id='input${input}DecayBoost' class='numberInput' type='number' value='${this.inputs[input].decayBoost}' step='0.01'></input>
						Decay Rate: <input id='input${input}DecayRate' class='numberInput' type='number' value='${this.inputs[input].decayRate}' step='0.01'></input>
						Threshold: <input id='input${input}DecayThreshold' class='numberInput' type='number' value='${this.inputs[input].decayThreshold}' step='0.01'></input>
						Range: <input id='input${input}DecayRange' class='numberInput' type='number' value='${this.inputs[input].decayRange}' step='0.01'></input>
					</div>
				`

			editInputsPanel.appendChild(editInputItem);

			// this is populating the drop-down list of ranges and selecting the current range
			let inputRangesList = document.getElementById(`input${input}Range`);
			Object.keys(sound.signals).forEach(signal => {
				Object.keys(sound.signals[signal].ranges).forEach(range => {
					let rangeListElement = document.createElement('option');
					rangeListElement.setAttribute('value', range);
					rangeListElement.innerText = range;
					if (range === this.inputs[input].range) {
						rangeListElement.setAttribute('selected', true);
					}
					inputRangesList.appendChild(rangeListElement);
				})
			})

			// create the event listeners for the inputs
			let inputType = document.getElementById(`input${input}Type`)
			inputType.addEventListener('change', () => {
				this.inputs[input].type = inputType.value;
				this.displayInputs(); // updates in the track list
			})

			let inputValue = document.getElementById(`input${input}Value`)
			inputValue.addEventListener('change', () => {
				this.inputs[input].value = inputValue.value;
				this.displayInputs(); // updates in the track list
			})

			let inputRange = document.getElementById(`input${input}Range`)
			inputRange.addEventListener('change', () => {
				this.inputs[input].range = inputRange.value;
				this.showEditGUI(); // required because range min/max changes
				this.displayInputs(); // updates in the track list
			})

			let inputDeleteButton = document.getElementById(`deleteInput${input}`);
			inputDeleteButton.addEventListener('click', () => {
				this.inputs.splice(input, 1);
				this.showEditGUI();
				this.displayInputs();
			})

			let inputMin = document.getElementById(`input${input}Min`);
			inputMin.addEventListener('change', () => {
				this.inputs[input].min = inputMin.value;
				this.displayInputs();
			})

			let inputPeak = document.getElementById(`input${input}Peak`);
			inputPeak.addEventListener('change', () => {
				this.inputs[input].peak = inputPeak.value;
				this.displayInputs();
			})

			let inputMax = document.getElementById(`input${input}Max`);
			inputMax.addEventListener('change', () => {
				this.inputs[input].max = inputMax.value;
				this.displayInputs();
			})

			let inputRangeMin = document.getElementById(`input${input}RangeMin`);
			inputRangeMin.addEventListener('change', () => {
				this.inputs[input].getRange().min = inputRangeMin.value;
				this.displayInputs();
			})

			let inputRangeMax = document.getElementById(`input${input}RangeMax`);
			inputRangeMax.addEventListener('change', () => {
				this.inputs[input].getRange().max = inputRangeMax.value;
				this.displayInputs();
			})

			let inputDecayBoost = document.getElementById(`input${input}DecayBoost`)
			inputDecayBoost.addEventListener('change', () => {
				this.inputs[input].decayBoost = inputDecayBoost.value;
			})

			let inputDecayRate = document.getElementById(`input${input}DecayRate`)
			inputDecayRate.addEventListener('change', () => {
				this.inputs[input].decayRate = inputDecayRate.value;
			})

			let inputDecayThreshold = document.getElementById(`input${input}DecayThreshold`)
			inputDecayThreshold.addEventListener('change', () => {
				this.inputs[input].decayThreshold = inputDecayThreshold.value;
			})

			let inputDecayRange = document.getElementById(`input${input}DecayRange`)
			inputDecayRange.addEventListener('change', () => {
				this.inputs[input].decayRange = inputDecayRange.value;
			})
			
			
		} // end of list of inputs

		let newInputButton = document.createElement('button')
		newInputButton.setAttribute('id', 'newInputButton');
		newInputButton.innerText = 'Add New Input';
		editInputsPanel.appendChild(newInputButton);

		// adds a new input, automatically selects the range of first currently existing input,
		// otherwise it selects 'td_front_back' as a placeholder
		let inputAddButton = document.getElementById(`newInputButton`);
		inputAddButton.addEventListener('click', () => {
			let newInputRange = this.inputs[0] ? this.inputs[0].range : 'td_front_back'
			this.inputs.push(new Input({'range':newInputRange, 'type':'volume', 'value':'curr', 'min':0, 'peak':1, 'max':1}))
			console.log(this.inputs);
			this.showEditGUI();
			this.displayInputs();
		})

	}

	getJSON() {
		let preset = { 'fileName': this.fileName, 'gain' : this.userGainSlider.value, 'loopLength': this.loopLength, 'decayCutoff': this.decayCutoff }
		preset.inputs = this.inputs.map((input)=>{
			return {'range':input.range, 'type': input.type, 'value': input.value, 'min': input.min, 'peak': input.peak, 'max': input.max, 'decayRate': input.decayRate, 'decayRange': input.decayRange, 'decayBoost': input.decayBoost, 'decayThreshold': input.decayThreshold }
		})
		return preset;
	}
}


// A range is a selected range of the signal that tracks can control a track
class Range {
	constructor (range) {
		this.name = range.name;
		this.min = range.min ? range.min : 0.;
		this.max = range.max ? range.max : 0.;
		this.value = range.value ? range.value : 'curr';
		this.relative = range.relative ? range.relative : false;
	}

	update () {
		if (this.relative) {
			let channel = Signal.getChannel(this.name);
			let newValue = sound.signals[channel][this.value];
			if (this.max === null ) {
				this.max = Number(newValue.toFixed(2));
				this.min = Number(newValue.toFixed(2));
			}
			if (newValue > this.max) {
				this.max = Number(newValue.toFixed(2));
			}
			if (newValue < this.min) {
				this.min = Number(newValue.toFixed(2));
			}
		}
	}

	showGUI () {
		console.log("show GUI for range " + this.name);
	}
}

// Interfaces between ranges and tracks. A track can have several inputs.
class Input {
	constructor (input) {
		this.range = input.range;
		this.type = input.type;
		this.value = input.value; // 'curr', 'avg3', 'avg5', 'avg10'
		this.min = input.min;
		this.peak = input.peak;
		this.max = input.max;
		this.current = 0;
		this.playbackMin = input.playbackMin ? input.playbackMin : 1;
		this.playbackSpeedup = input.playbackSpeedup ? input.playbackSpeedup : 1;
		this.decayRate = input.decayRate ? input.decayRate : 0.5;
		this.decayBoost = input.decayBoost ? input.decayBoost : 0.2;
		this.decayThreshold = input.decayThreshold ? input.decayThreshold : 0.7;
		this.decayRange = input.decayRange ? input.decayRange: 0.2;
		this.decayTarget = null;
		this.decayValue = 0;
	}

	updateDecay (value) {
		// if the decay Target is not yet defined, set it to the current value and return 1 or no decay.
		this.current = value;
		if (this.decayTarget === null) {
			this.decayTarget = value;
			//this.decayValue = this.decayThreshold;
			this.decayValue = this.decayBoost;
			return 1;
		}


		// if the value is within the range of the decay target, apply one step of decay and return the new decay value.
		if ( Math.abs(this.decayTarget - value) < this.decayRange ) {
			this.decayValue = this.decayValue * this.decayRate;
			return this.decayValue;
		}

		// if you get this far it means the value is outside of the the range
		this.decayValue = this.decayValue + this.decayBoost
		if (this.decayValue > this.decayThreshold) {
			this.decayTarget = value;
		}
		if (this.decayValue > 1) {this.decayValue = 1}
		return this.decayValue;
	}

	getRange () {
		let rangeToSend = null
		Object.keys(sound.signals).forEach(signal => {
			Object.keys(sound.signals[signal].ranges).forEach(range => {
				if (range === this.range) {
					rangeToSend = sound.signals[signal].ranges[this.range];
				}
			})
		})
		return rangeToSend
	}
}



/// HANDLING OSC RECORDINGS/PLAYBACK

class OSCPlayer {
	constructor() {
		this._playing = false;
		this._currentEvent = 0;
		this._nextEvent = null;
		this.timeout = null;
		this.events = [];

		this.loadOSCEvents = () => {
			let fileName = document.getElementById('OSCEventFile').value.split('\\');
			fileName = fileName[fileName.length - 1];

			if (fileName !== '') {
				fetch(eventsFilePath + fileName)
					.then(response => response.text())
					.then(events => {
						this.events = JSON.parse(events);
						document.getElementById('toggleOSC').removeAttribute('disabled');
						document.getElementById('resetOSC').removeAttribute('disabled');
					})
			}
		}

		this.toggleOSC = () => {
			let button = document.getElementById('toggleOSC');
			if (this._playing) {
				this.cancelNextEvent();
				button.innerText = 'Play OSC';
			} else {
				this.playOSC();
				button.innerText = 'Pause OSC';
			}
		}

		this.playOSC = () => {
			console.log('playing OSC');
			this._playing = true;
			this.playEvent(this._currentEvent);
		}

		this.playEvent = (i) => {
			if (i < this.events.length) {
				this._currentEvent = i;
				// message processing goes here!
				console.log(this.events[i].message);
				Signal.processMessage(this.events[i].message);
				this.sequenceNextEvent(i);
			}
		}

		this.sequenceNextEvent = (i) => {
			if (i + 1 < this.events.length) {
				let delay = this.events[i+1].time - this.events[i].time;
				// SAMPLE RATE PATCH - for WSAS07 uncomment this
				//delay = delay/4;
				this.timeout = setTimeout(this.playEvent, delay, i+1);
			} else { console.log('reached end of OSC')};
		}

		this.cancelNextEvent = () => {
			clearTimeout(this.timeout);
			this._playing = false;
		}

		this.setOSCStep = (step) => {
			this._currentEvent = step;
		}

		this.resetOSC = () => {
			if (this.playing) {
				this.toggleOSC();
			}
			oscPlayer.setOSCStep(0);
		}
	}

	get playing() {
		return this._playing;
	}
}

class OSCRecorder {
	constructor() {
		this._recording = false;
		this.timeStarted = null;
		let events = [];
		console.log('created OSC recorder');

		this.startRecording = () => {
			this._recording = true;
			this.timeStarted = Date.now();
			document.getElementById('recordOSC').innerText = 'Stop Recording OSC';
			console.log('OSC started recording at ' + this.timeStarted);
		}

		this.stopRecording = () => {
			this._recording = false;
			console.log('OSC stopped recording');
			document.getElementById('recordOSC').innerText = 'Start Recording OSC';
			console.log(events);
			this.saveEvents();
			this.timeStarted = null;
			events = [];
		}

		this.toggleRecording = () => {
			if (this._recording) {
				this.stopRecording();
			} else this.startRecording();
		}

		this.receiveMessage = (message) => {
			if (this._recording) {
				events.push({'time': Date.now() - this.timeStarted, 'message': message});
			}
		}

		this.saveEvents = () => {
			console.log('saving events to file');
			// this is a hacky way of saving a text file
		    var a = document.createElement("a");
		    var file = new Blob([JSON.stringify(events)], {type: 'text/plain'});
		    a.href = URL.createObjectURL(file);
		    a.download = 'oscEvents.txt';
		    a.innerHTML = a.download;
		    let dummy = document.getElementById('resonancePlayer');
		    dummy.appendChild(a);
		    a.click();
		    dummy.removeChild(a);
		    URL.revokeObjectURL(a.href);
		}

		this.play = () => {
			playOSCEvents(events);
		}
	}

	set recording (value) {
		console.log('recording: ' + value);
		this._recording = value;
	}

	get recording () {
		return this._recording;
	}
}

// INITIALIZE ENVIRONEMENT BEFORE LOADING AUDIO

// assign proper functions to GUI buttons
window.onload = function () {
	document.getElementById('startContextButton').addEventListener("click", () => { startAudio(defaultPreset) });
	document.getElementById('loadPresetButton').addEventListener('click', () => { loadPreset() });
	document.getElementById('savePresetButton').addEventListener('click', () => { savePreset() });
	document.getElementById('loadOSC').addEventListener('click', () => { oscPlayer.loadOSCEvents() });
	document.getElementById('toggleOSC').addEventListener("click", () => { oscPlayer.toggleOSC() });
	document.getElementById('resetOSC').addEventListener("click", () => { oscPlayer.resetOSC() });
	document.getElementById('recordOSC').addEventListener("click", () => { oscRecorder.toggleRecording() });
}

// websocket for receiving messages
const socket = io('http://127.0.0.1:5000');

socket.on('connect', function() {
	socket.emit('my event', {data: "New connection!"})
})

socket.on('event', function(message){
	oscRecorder.receiveMessage(message);
	Signal.processMessage(message);
});

// instantiate objects

const oscPlayer = new OSCPlayer();
const oscRecorder = new OSCRecorder();

// handling presets
function loadPreset() {
	let fileName = document.getElementById('presetFileInput').value.split('\\');
	fileName = fileName[fileName.length - 1];

	if (fileName !== '') { // check if input field is blank
		fetch('static/playerPresets/' + fileName)
			.then(response => response.text())
			.then(preset => {
				startAudio(JSON.parse(preset));
			})
	} else {
		console.log('please select a preset file from the playerPresets folder');
	}
}

function savePreset() {
	console.log('saving app state as preset');

	let savedPreset = {};
	savedPreset.signals = Object.keys(sound.signals).map(signal => sound.signals[signal].getJSON());
    savedPreset.tracks = sound.tracks.map(track => track.getJSON()); // saves tracks JSON
    
    var file = new Blob([JSON.stringify(savedPreset)], {type: 'text/plain'});

    // this is a way of saving a file from the front-end
    var a = document.createElement("a");
    a.href = URL.createObjectURL(file);
    a.download = 'preset.txt';
    a.innerHTML = a.download;
    document.getElementById('resonancePlayer').appendChild(a);
    a.click();
    document.getElementById('resonancePlayer').removeChild(a);
    URL.revokeObjectURL(a.href);
}


// initializing page
function startAudio(preset) {
	console.log('audio started!');

	// remove the start context button
	const button = document.getElementById('startContextButton')
	if (button) {button.parentNode.removeChild(button);}

	document.getElementById('mainControls').removeAttribute('style');

	sound.context = new AudioContext();
	sound.context.suspend();
	Tone.context = sound.context;

	sound.masterGain = sound.context.createGain();
	sound.filter = new Tone.Filter(8000, 'lowpass');

	Tone.connect(sound.masterGain, sound.filter);
	sound.filter.connect(sound.context.destination);

	// activate main GUI buttons
	document.getElementById('savePresetButton').removeAttribute('disabled');

	const playButton = document.getElementById('startAudio');
	playButton.addEventListener('click', ()=>{
		sound.context.resume();
	})

	const stopButton = document.getElementById('stopAudio');
	stopButton.addEventListener('click', ()=>{sound.context.suspend()})

	const masterGainSlider = document.getElementById('masterGain');
	sound.masterGain.gain.value = Math.pow(10, masterGainSlider.value/20);
	masterGainSlider.addEventListener('input', ()=> {
		sound.masterGain.gain.setTargetAtTime(Math.pow(10, masterGainSlider.value/20),sound.context.currentTime, 0.1);
	}, false);

	const newTrackButton = document. getElementById('newTrack');
	newTrackButton.addEventListener('click', () => {
		let filename = document.getElementById('newTrackFileInput').value.split('\\');
		if (filename != '') {
			filename = filename[filename.length - 1];
			let newTrack = loadTrack({fileName: filename, inputs: []});
			document.getElementById('newTrackFileInput').value = '';
			console.log('added track ' + filename);
			newTrack.showEditGUI();
		} else {
			console.log('please select a sound file before adding a Track');
		}
	})

	// initalize list of channels
	preset.signals.map(signal => loadSignal(signal));

	//load the selected preset
	preset.tracks.map(track => loadTrack(track));

	sound.context.resume();
}

function loadTrack(track) {
	let newTrack = new Track(track)
	sound.tracks.push(newTrack);
	return newTrack;
}

function loadSignal(signal) {
	sound.signals[signal.channel] = new Signal(signal);
}
