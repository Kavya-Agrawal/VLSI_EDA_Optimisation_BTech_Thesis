// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.27511550;
  double density_weight = 0.55862373;
  double prefix_weight = 0.11698384;
  double neighborhood_weight = 0.22700131;
  double late_weight = 0.04332189;
  double critical_weight = 0.34405808;
  unsigned budget = 24;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
