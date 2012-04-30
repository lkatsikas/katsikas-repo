% COMMDVBC_INIT Preloads workspace variables for demo models commdvbc and
% commdvbc_fixpt and System objects of commsysobjdvbcdemo.

% Copyright 2008-2010 The MathWorks, Inc.
% $Revision: 1.1.6.1 $  $Date: 2010/08/29 23:23:43 $

prmDVBC.bitsPerByte          = 8;
prmDVBC.bitsPerMTpl          = 6;
prmDVBC.MPEG2DatRateBitPerS  = 9.6e6;
prmDVBC.rawMPEG2DataPcktLen  = 184;
prmDVBC.MPEG2TrnsprtPcktLen  = 188;
prmDVBC.MPEG2TrnsprtFramePer = prmDVBC.bitsPerByte * prmDVBC.MPEG2TrnsprtPcktLen / prmDVBC.MPEG2DatRateBitPerS;
prmDVBC.MPEG2PcktsPerSprFrm  = 8;
prmDVBC.MPEG2TrnsSuperFrame  = prmDVBC.MPEG2PcktsPerSprFrm * prmDVBC.MPEG2TrnsprtPcktLen;
prmDVBC.PRBSSeqPeriodBytes   = prmDVBC.MPEG2TrnsSuperFrame - 1;
prmDVBC.PRBSSeqPeriodBits    = prmDVBC.bitsPerByte * prmDVBC.PRBSSeqPeriodBytes;
prmDVBC.RSCodewordLength     = 204;
prmDVBC.CableChanFrameLen    = prmDVBC.RSCodewordLength * (prmDVBC.bitsPerByte / prmDVBC.bitsPerMTpl);
prmDVBC.CableChanFrmPeriod   = prmDVBC.MPEG2TrnsprtFramePer;
prmDVBC.TxInterpRxDecimFctr  = 8;
prmDVBC.CableSymbolPeriod    = prmDVBC.CableChanFrmPeriod / (prmDVBC.TxInterpRxDecimFctr * prmDVBC.CableChanFrameLen);
prmDVBC.TxIntrpRxDecmGrpDly  = 8;
prmDVBC.TxRxSymbolSampDelay  = prmDVBC.CableChanFrameLen + (2 * prmDVBC.TxIntrpRxDecmGrpDly);
prmDVBC.DeintrlvrAlignDelay  = prmDVBC.RSCodewordLength  - (2 * prmDVBC.TxIntrpRxDecmGrpDly) * (prmDVBC.bitsPerMTpl / prmDVBC.bitsPerByte);
prmDVBC.QAMSymbolMapping     = [...
  44 45 41 40 52 54 62 60 46 47 43 42 53 55 63 61 ...
  38 39 35 34 49 51 59 57 36 37 33 32 48 50 58 56 ...
  8 10  2  0 16 17 21 20  9 11  3  1 18 19 23 22 ...
  13 15  7  5 26 27 31 30 12 14  6  4 24 25 29 28 ];
prmDVBC.ConvIntlNumBranches = 12;
prmDVBC.ConvIntlCellDepth = 17;

% [EOF]
