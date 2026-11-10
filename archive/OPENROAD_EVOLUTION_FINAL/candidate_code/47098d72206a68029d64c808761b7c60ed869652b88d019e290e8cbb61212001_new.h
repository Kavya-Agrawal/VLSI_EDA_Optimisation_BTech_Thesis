// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.04892545;
  double density_weight = 0.47885643;
  double prefix_weight = 0.12891884;
  double neighborhood_weight = 0.01850763;
  double late_weight = 0.21081602;
  double critical_weight = 0.03671850;
  unsigned budget = 20;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
